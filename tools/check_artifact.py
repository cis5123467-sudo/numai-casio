#!/usr/bin/env python3
"""Check the final G3A's icon pixels and compiled physical-key bridge."""
from pathlib import Path
from struct import iter_unpack
import hashlib
from PIL import Image
from elftools.elf.elffile import ELFFile
root = Path(__file__).resolve().parents[1]
path = root/'release/numai-casio-v0.1.4-r1.g3a'
raw = path.read_bytes()
assert bytes(x^255 for x in raw[:8])==b'USBPower'
assert int.from_bytes(bytes(x^255 for x in raw[16:20]),'big')==len(raw)
for offset,name,background in [(0x1000,'icon.png',(255,255,255)),(0x4000,'selected.png',(255,181,43))]:
    im=Image.open(root/'build'/name).convert('RGB')
    assert im.size==(92,64)
    # MPM draws its own label at y=45; every source pixel there must be clear.
    assert all(im.getpixel((x,y))==background for y in range(44,64) for x in range(92))
    expected=b''.join((((r>>3)<<11 | (g>>2)<<5 | b>>3)).to_bytes(2,'big') for r,g,b in (im.getpixel((x,y)) for y in range(64) for x in range(92)))
    assert raw[offset:offset+len(expected)]==expected
with (root/'build/NumAI.elf').open('rb') as f:
    elf=ELFFile(f)
    symbols=elf.get_section_by_name('.symtab')
    symbol=next(s for s in symbols.iter_symbols() if s.name=='_keymap')
    section=elf.get_section(symbol['st_shndx'])
    start=symbol['st_value']-section['sh_addr']
    table=dict(iter_unpack('>ii',section.data()[start:start+symbol['st_size']]))
    expected={0xad:16,0x82:15,0x83:54,0x52:53,0x51:55,0xab:56,0x07:57,
        0xa7:58,0xa8:59,0xa9:60,0xaa:61,0xae:28,0xaf:18,0x61:14,0x56:62}
    assert all(table.get(k)==v for k,v in expected.items()),table
print(f'G3A metadata, 92x64 icon payloads/label clearance, native key table passed; {len(raw)} bytes')
print('SHA256 '+hashlib.sha256(raw).hexdigest())
