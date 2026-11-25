#!/usr/bin/env python3
"""Run host integration checks against production input/editor handlers."""
from pathlib import Path
import os
import platform
import subprocess
import tempfile
import sys
root = Path(__file__).resolve().parents[1]
sdk = Path(os.environ.get('CASIO_SDK','/tmp/numplay-toolchain/prefix'))
include = os.environ.get('CASIO_HOST_HEADERS')
if include is None:
    include = subprocess.check_output([sdk/'bin/fxsdk','path','include'],text=True).strip()
test = sys.argv[1] if len(sys.argv)>1 else 'native_controls'
assert test in ['native_controls','chemistry_content','physics_content']
sources = ['tests/'+test+'.c', *['src/'+name+'.c' for name in ['cas','topics','physics','chemistry','units','solvers','scriptstore','mathview','organic']]]
if test in ['chemistry_content','physics_content']: sources.append('tests/pinned_chemistry.c')
with tempfile.TemporaryDirectory(prefix='numai-controls-') as folder:
    exe = Path(folder)/'controls'
    flags = ['-Wl,-dead_strip'] if platform.system()=='Darwin' else ['-Wl,--gc-sections']
    subprocess.run([os.environ.get('CC','cc'),'-std=c11','-w','-ffunction-sections','-fdata-sections',
        '-DPLATFORM_DEVICE=1','-idirafter',include,'-I',str(root/'src'),
        *[str(root/s) for s in sources],*flags,'-lm','-o',str(exe)],check=True)
    subprocess.run([exe],cwd=folder,check=True)
