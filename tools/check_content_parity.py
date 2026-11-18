#!/usr/bin/env python3
"""Reject any delivered course/equation content that differs from the pinned NumWorks release."""
from pathlib import Path
import hashlib
import json
root=Path(__file__).resolve().parents[1]
m=json.loads((root/'data/numworks-0.1.3-parity.json').read_text())
for name,expected in m['files'].items():
    actual=hashlib.sha256((root/name).read_bytes()).hexdigest()
    assert actual==expected,f'Content mismatch against NumWorks {m["release"]}: {name}'
    content=(root/name).read_bytes()
    blob=hashlib.sha1(b'blob '+str(len(content)).encode()+b'\0'+content).hexdigest()
    assert blob==m['git_blobs'][name],f'GitHub blob mismatch: {name}'
print(f'All {len(m["files"])} curriculum/equation/unit source files match NumWorks {m["release"]} at {m["commit"]}.')
