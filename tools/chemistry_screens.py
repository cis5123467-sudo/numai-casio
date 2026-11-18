#!/usr/bin/env python3
"""Compatibility entry point for the exact NumWorks Chemistry navigation test."""
from pathlib import Path
import subprocess
import sys
subprocess.run([sys.executable,Path(__file__).with_name('course_screens.py'),'chemistry'],check=True)
