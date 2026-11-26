#!/usr/bin/env python3
"""Open and scroll every pinned Physics or Chemistry entry in the release package."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import os
import subprocess
import re
import sys
from PIL import Image,ImageChops
root=Path(__file__).resolve().parents[1]
source=(root/'data/aqa_catalog_numworks_0.1.4.inc').read_text()
subject=sys.argv[1] if len(sys.argv)>1 else 'physics'
assert subject in ['physics','chemistry','biology']
names=['phys_energy','phys_electric','phys_particles','phys_atoms','phys_forces','phys_waves','phys_magnets','phys_space','phys_key','phys_practicals','science_skills']
if subject=='chemistry':
    names=['chem_atoms','chem_bonds','chem_amount','chem_changes','chem_energy','chem_rates','chem_organic','chem_analysis','chem_atmosphere','chem_resources','chem_key','chem_practicals','science_skills']
if subject=='biology':
    names=['bio_cells','bio_org','bio_infection','bio_energy','bio_control','bio_genetics','bio_ecology','bio_key','bio_practicals','science_skills']
expected={'physics':131,'chemistry':162,'biology':135}[subject]
course_row={'physics':5,'chemistry':7,'biology':6}[subject]
cases=[]
for i,name in enumerate(names):
    body=re.search(r'static const Topic '+name+r'\[\] = \{(.*?)\n\};',source,re.S)[1]
    count=len(re.findall(r'\b[SHK]\(',body));cases.append((i,name,count))
assert sum(n for i,name,n in cases)==expected
base=root/f'verification/{subject}-parity-v0.1.4-r1';base.mkdir(parents=True,exist_ok=True)
emulator=os.environ.get('CASIO_EMULATOR','/tmp/numplay-toolchain/emu-build/emucasiocalc')
def test(item):
    chapter,name,count=item;folder=base/name;folder.mkdir(exist_ok=True)
    for start in range(0,count,8):
        batch=folder/f'batch-{start:02}';batch.mkdir(exist_ok=True)
        script='scale 1, wait 0.7s, SHIFT, EXE, EXE, '+'DOWN, '*course_row+'EXE, '+'DOWN, '*chapter+'EXE, '+'DOWN, '*start
        for row in range(start,min(start+8,count)):
            script+=f'EXE, wait 0.6s, shot {row:02}-notes.png, '+'DOWN, '*6+f'wait 0.4s, shot {row:02}-scroll.png, EXIT, DOWN, '
        script+='MENU'
        script=re.sub(r'\b(SHIFT|EXE|EXIT|DOWN),',r'\1, wait 0.8s,',script)
        p=subprocess.run([emulator,'--headless','--model','cg50','--keys',script,root/'release/numai-casio-v0.1.4-r1.g3a'],cwd=batch,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=180)
        (batch/'run.log').write_text(p.stdout)
        assert p.returncode==0 and 'add-in exited after' in p.stdout and 'stopped with an error' not in p.stdout,p.stdout
        for image in batch.glob('*.png'):(folder/image.name).write_bytes(image.read_bytes())
    for row in range(count):
        notes=Image.open(folder/f'{row:02}-notes.png');scroll=Image.open(folder/f'{row:02}-scroll.png')
        assert notes.size==(396,224)
        assert ImageChops.difference(notes.crop((0,0,396,21)),scroll.crop((0,0,396,21))).getbbox() is None,(name,row)
    return name,count
with ThreadPoolExecutor(max_workers=3) as pool:
    for name,n in pool.map(test,cases):print(f'{name}: {n} pages opened and scrolled',flush=True)
print(f'All {expected} {subject} entries passed SuperH runtime navigation checks.')
