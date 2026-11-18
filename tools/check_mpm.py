#!/usr/bin/env python3
"""Check file discovery and metadata with MPM's C code and a host BFile shim."""
import argparse
from pathlib import Path
import re
import subprocess
import tempfile

ap=argparse.ArgumentParser(description=__doc__)
ap.add_argument('mpm_source',type=Path,help='MPM v1.1 source tree')
ap.add_argument('addin',type=Path)
args=ap.parse_args()
p=args.addin.resolve()
src=args.mpm_source.resolve()
raw=p.read_bytes()
assert p.suffix=='.g3a'
assert len(raw)<=2**21
assert bytes(b^255 for b in raw[:8])==b'USBPower'
assert int.from_bytes(bytes(b^255 for b in raw[16:20]),'big')==len(raw)
mpm=(src/'main.c').read_text()
find=mpm[mpm.index('static bool FindAddins_add'):mpm.index('//=== MMU tests')]
meta=(src/'addins.c').read_text()
meta=meta[meta.index('void AddIn_load_metadata'):meta.index('void AddIn_render_icon')]
lists=(src/'addins.c').read_text()
extend=lists[lists.index('struct AddIn *AddInList_extend('):]
util=(src/'util.c').read_text()
paths=util[util.index('int PathStrlen('):util.index('char *PathToStr(')]
code=r'''
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addins.h"
#include "casiowin.h"
static const char *filename;
static long size;
static unsigned char *buffer;
void *CW_malloc(size_t n) { return malloc(n); }
void CW_free(void *p) { free(p); }
int CW_BFile_FindFirst(const u16 *p, int *h, u16 *f, struct CW_BFile_FileInfo *i) {
    static const u16 expected[] = u"\\\\fls0\\*.g3a";
    assert(!memcmp(p, expected, sizeof expected));
    size_t n=strlen(filename);
    if(n<4 || strcmp(filename+n-4, ".g3a")) return -1;
    for(size_t j=0; j<=n; j++) f[j]=(unsigned char)filename[j];
    *h=1;
    i->type=CW_BFile_Type_Addin;
    i->file_size=(u32)size;
    return 0;
}
int CW_BFile_FindNext(int h, u16 *f, struct CW_BFile_FileInfo *i) {
    (void)f; (void)i; assert(h==1); return -16;
}
int CW_BFile_FindClose(int h) { assert(h==1 || h==-1); return 0; }
int CW_BFile_Open(const u16 *p, int mode) {
    (void)mode; (void)p; return 2;
}
int CW_BFile_Close(int h) { assert(h==2); return 0; }
int CW_BFile_Block(int h, int offset, void **out) {
    assert(h==2);
    if(offset<0 || offset>=size) return -1;
    *out=buffer+offset;
    return 0;
}
int FindAddins(struct AddInList *);
int main(int argc, char **argv) {
    assert(argc==2);
    filename=strrchr(argv[1],'/');
    filename=filename?filename+1:argv[1];
    FILE *f=fopen(argv[1],"rb");
    assert(f);
    assert(!fseek(f,0,SEEK_END));
    size=ftell(f);
    assert(size>=0x7002 && size<=0x200000 && size-0x7000<=0x370000);
    rewind(f);
    buffer=malloc(size);
    assert(buffer && fread(buffer,1,size,f)==(size_t)size);
    fclose(f);
    struct AddIn a[2];
    struct AddInList l={.size=0,.capacity=2,.addins=a};
    assert(FindAddins(&l)==1 && l.size==1);
    AddIn_load_metadata(&a[0]);
    assert(a[0].metadata_loaded && !a[0].metadata_error);
    assert(!strncmp(a[0].name,"NumAI",16));
    for(int i=0;i<6;i++) assert(a[0].icon.blocks[i]);
    printf("MPM v1.1 discovered %s as %.16s (%.10s; %u bytes), with icon blocks.\n",
           filename,a[0].name,a[0].version,a[0].filesize);
    free(a[0].path);
    free(buffer);
}
'''
with tempfile.TemporaryDirectory(prefix='mpm-check-') as tmp:
    names=sorted(set(re.findall(r"CW_VAR\(.*?,\s*(\w+)\)",(src/"casiowin.h").read_text())))
    (Path(tmp)/"casiowin.inc").write_text("\n".join(f"#define CW_VARIABLE_{k} {i}" for i,k in enumerate(names)))
    c=Path(tmp)/'check.c'
    c.write_text(code+find+meta+extend+paths)
    exe=Path(tmp)/'check'
    subprocess.run(['cc','-std=gnu11','-Wno-int-to-pointer-cast','-I'+tmp,'-I'+str(src),str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe),str(p)],check=True)
