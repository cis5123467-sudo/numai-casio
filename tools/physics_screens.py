#!/usr/bin/env python3
"""Run the exact NumWorks Physics navigation test."""
from pathlib import Path
import subprocess
import sys
subprocess.run([sys.executable,Path(__file__).with_name('course_screens.py'),'physics'],check=True)
