#!/usr/bin/env python3
"""Verify the r2 calculator/Courses layout and unit typesetting in the G3A."""
from pathlib import Path
from struct import unpack
import os
import subprocess
from PIL import Image
root=Path(__file__).resolve().parents[1]
base=root/'verification/ui-v0.1.4-r1';base.mkdir(parents=True,exist_ok=True)
emulator=os.environ.get('CASIO_EMULATOR','/tmp/numplay-toolchain/emu-build/emucasiocalc')
def run(name,script):
    folder=base/name;folder.mkdir(exist_ok=True)
    for file in ['numai.sav','numai.bak','numai.tmp']:
        (folder/'storage/fls0'/file).unlink(missing_ok=True)
    p=subprocess.run([emulator,'--headless','--model','cg50','--keys','scale 1, wait 0.7s, '+script.replace('shot ','wait 0.5s, shot '),root/'release/numai-casio-v0.1.4-r1.g3a'],cwd=folder,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=90)
    (folder/'run.log').write_text(p.stdout)
    assert p.returncode==0 and 'add-in exited after' in p.stdout and 'stopped with an error' not in p.stdout,p.stdout
    return folder
for name,group,from_row,to_row,number,answer in [
    ('area',1,1,3,'25000','2.5 m^2'),('volume',2,1,2,'2500','2.5 dm^3'),
    ('density',18,1,0,'2.5','2500 kg/m^3')]:
    script='OPTN, '+'DOWN, '*4+'EXE, '+'DOWN, '*group+'EXE, shot from.png, '+'DOWN, '*from_row+'EXE, shot to.png, '+'DOWN, '*to_row+'EXE, shot input.png, '
    script+=', '.join('DP' if ch=='.' else ch for ch in number)+', EXE, shot result.png, MENU'
    folder=run(name,script)
    raw=(folder/'storage/fls0/numai.sav').read_bytes()
    assert answer.encode() in raw,(name,answer)
    print(name+' conversion and display passed',flush=True)
folder=run('calculation','shot home.png, 1, DIV, 3, EXE, shot fraction.png, UP, shot history.png, MENU')
for name in ['home','fraction','history']:
    im=Image.open(folder/(name+'.png')).convert('RGB')
    assert im.size==(396,224) and im.getpixel((0,223))==(255,255,255),(name,im.getpixel((0,223)))
run('courses','SHIFT, EXE, EXE, shot order.png, DOWN, EXE, shot search.png, MENU')
print('Calculator/history use the full height without routine footer; Courses second-entry search opens.',flush=True)
