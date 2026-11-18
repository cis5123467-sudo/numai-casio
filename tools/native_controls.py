#!/usr/bin/env python3
"""Run host integration checks against production input/editor handlers."""
from pathlib import Path
import os
import platform
import subprocess
import tempfile
root = Path(__file__).resolve().parents[1]
sdk = Path(os.environ.get('CASIO_SDK','/tmp/numplay-toolchain/prefix'))
include = subprocess.check_output([sdk/'bin/fxsdk','path','include'],text=True).strip()
sources = ['tests/native_controls.c', *['src/'+name+'.c' for name in ['cas','topics','physics','chemistry','units','solvers','scriptstore','mathview']]]
with tempfile.TemporaryDirectory(prefix='numai-controls-') as folder:
    exe = Path(folder)/'controls'
    flags = ['-Wl,-dead_strip'] if platform.system()=='Darwin' else ['-Wl,--gc-sections']
    subprocess.run([os.environ.get('CC','cc'),'-std=c11','-w','-ffunction-sections','-fdata-sections',
        '-DPLATFORM_DEVICE=1','-idirafter',include,'-I',str(root/'src'),
        *[str(root/s) for s in sources],*flags,'-lm','-o',str(exe)],check=True)
    subprocess.run([exe],cwd=folder,check=True)
