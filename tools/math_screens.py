#!/usr/bin/env python3
"""Render bracket, fraction, power and symbol regression cases in the shipped G3A."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import os
import subprocess
from PIL import Image, ImageDraw
root = Path(__file__).resolve().parents[1]
emulator = os.environ.get('CASIO_EMULATOR', '/tmp/numplay-toolchain/emu-build/emucasiocalc')
letters = dict(zip('abdefghijklmnopqrstuvwxyz', ['XOT','FRAC','POWER','SQUARE','EXPFUN','COMMA','SIN','COS','TAN','LPAR','RPAR','7','8','9','4','5','6','MULT','DIV','1','2','3','PLUS','MINUS','0']))
keys = {'*':'MULT','/':'DIV','^':'POWER','(':'LPAR',')':'RPAR','+':'PLUS','-':'MINUS','.':'DP',',':'COMMA'}
cases = ['3*(1/2+2)*4','2((1+2))*3','1/2+3/4','(1+2)/(3+4)', '1/(1+1/2)',
         '(2+3)^2','2^(-3)','2^(1/2)','2^(3^2)','(1/2)^2','sqrt(2)+2*pi','sqrt(1/2)',
         '(3+4)*(5-2)','2*3*4','1/3','(1+2)^(-2/3)','(2^3)^2','(1/2)^(3/4)','(1/(2+3))^(-2)',
         '1/2^2','2^(-1/2)+3','(1/2)^(-2)','2^(123/456)','(12/345)^(67/89)']
base = root / 'verification/math-v0.1.4'
base.mkdir(parents=True,exist_ok=True)
def run(item):
    i, expression = item
    folder = base / f'{i:02}'
    folder.mkdir(exist_ok=True)
    # Remove only generated runtime saves in this dedicated test case.
    for name in ['numai.sav','numai.bak','numai.tmp']:
        (folder/'storage/fls0'/name).unlink(missing_ok=True)
    script = 'scale 1, wait 0.7s, VARS, EXE, EXIT, '
    for ch in expression:
        script += ('ALPHA, ' + letters[ch] if ch.isalpha() else keys.get(ch,ch)) + ', '
    script += 'wait 0.5s, shot input.png, EXE, wait 0.5s, shot result.png, MENU'
    p = subprocess.run([emulator,'--headless','--model','cg50','--keys',script,root/'release/numai-casio-v0.1.4.g3a'],cwd=folder,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=90)
    (folder/'run.log').write_text(p.stdout)
    assert p.returncode == 0 and 'add-in exited after' in p.stdout and 'stopped with an error' not in p.stdout,p.stdout
    assert Image.open(folder/'result.png').size == (396,224)
    return i,expression
with ThreadPoolExecutor(max_workers=3) as pool:
    for i,e in pool.map(run,enumerate(cases)): print(f'{i:02}: {e}',flush=True)
for kind in ['input','result']:
    sheet=Image.new('RGB',(396*3,250*((len(cases)+2)//3)),'white')
    draw=ImageDraw.Draw(sheet)
    for i,e in enumerate(cases):
        x,y=i%3*396,i//3*250
        draw.text((x+5,y+4),e,fill='black')
        sheet.paste(Image.open(base/f'{i:02}'/f'{kind}.png'),(x,y+24))
    sheet.save(base/f'{kind}-contact.png')
print(f'{len(cases)} fraction, bracket, power and symbol cases rendered without emulator errors')
