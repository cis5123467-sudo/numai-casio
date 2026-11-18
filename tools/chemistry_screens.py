#!/usr/bin/env python3
"""Exercise every Chemistry card and its Key ideas view in the release G3A."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import json
import os
import subprocess
import re
import sys
from PIL import Image, ImageChops
root=Path(__file__).resolve().parents[1]
data=json.loads((root/'data/chemistry_revision.json').read_text())
base=root/'verification/chemistry-v0.1.3-r1'
base.mkdir(parents=True,exist_ok=True)
emulator=os.environ.get('CASIO_EMULATOR','/tmp/numplay-toolchain/emu-build/emucasiocalc')
def test(item):
    chapter,(name,section)=item
    folder=base/name; folder.mkdir(exist_ok=True)
    for file in ['numai.sav','numai.bak','numai.tmp']:
        (folder/'storage/fls0'/file).unlink(missing_ok=True)
    entries=[True]*len(section['topics'])
    if name not in ['chem_changes','chem_key']: entries.insert(0,False)
    for start in range(0,len(entries),8):
        batch=folder/f'batch-{start:02}'; batch.mkdir(exist_ok=True)
        script='scale 1, wait 0.7s, SHIFT, EXE, EXE, '+'DOWN, '*7+'EXE, '+'DOWN, '*chapter+'EXE, '+'DOWN, '*start
        for row in range(start,min(start+8,len(entries))):
            script+=f'EXE, wait 0.4s, shot {row:02}-notes.png, '
            if entries[row]: script+=f'EXE, wait 0.4s, shot {row:02}-key.png, EXIT, '
            script+='DOWN, '*6+f'wait 0.3s, shot {row:02}-scroll.png, EXIT, DOWN, '
        script+='MENU'
        # Allow full notes redraws and stay below the emulator's 512-step limit.
        script=re.sub(r'\b(SHIFT|EXE|EXIT|DOWN),',r'\1, wait 0.8s,',script)
        p=subprocess.run([emulator,'--headless','--model','cg50','--keys',script,root/'release/numai-0.1.3-r1.g3a'],cwd=batch,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=180)
        (batch/'run.log').write_text(p.stdout)
        assert p.returncode==0 and 'add-in exited after' in p.stdout and 'stopped with an error' not in p.stdout,p.stdout
        for image in batch.glob('*.png'): (folder/image.name).write_bytes(image.read_bytes())
    for row,has_key in enumerate(entries):
        notes=Image.open(folder/f'{row:02}-notes.png')
        assert notes.size==(396,224)
        if has_key:
            key=Image.open(folder/f'{row:02}-key.png')
            assert ImageChops.difference(notes,key).getbbox(),(name,row,'did not open Key ideas')
    return name,len(entries),sum(entries)
counts=[]
with ThreadPoolExecutor(max_workers=3) as pool:
    cases=list(enumerate(data.items()))
    if len(sys.argv)>1: cases=[item for item in cases if item[1][0]==sys.argv[1]]
    for name,n,k in pool.map(test,cases):
        print(f'{name}: {n} notes pages and {k} Key ideas views passed',flush=True);counts.append((n,k))
if len(sys.argv)==1: assert sum(n for n,k in counts)==162 and sum(k for n,k in counts)==151
print(f'{sum(n for n,k in counts)} Chemistry cards and {sum(k for n,k in counts)} Key ideas views passed in the SuperH G3A.')
