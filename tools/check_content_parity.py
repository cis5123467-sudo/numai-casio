#!/usr/bin/env python3
"""Reject any delivered course/equation content that differs from the pinned NumWorks release."""
from pathlib import Path
import hashlib
import json
root=Path(__file__).resolve().parents[1]
m=json.loads((root/'data/numworks-0.1.4-parity.json').read_text())
for name,expected in m['files'].items():
    actual=hashlib.sha256((root/name).read_bytes()).hexdigest()
    assert actual==expected,f'Content mismatch against NumWorks {m["release"]}: {name}'
    content=(root/name).read_bytes()
    blob=hashlib.sha1(b'blob '+str(len(content)).encode()+b'\0'+content).hexdigest()
    assert blob==m['git_blobs'][name],f'GitHub blob mismatch: {name}'
# Historical manifests contain only verbatim files. The NumWorks reorganisation
# added a path prefix to these includes, while the Casio project stays flat.
for name, expected in m.get('flattened_includes', {}).items():
    source = (root / name).read_bytes().replace(b'"cas.h"', b'"calculation/cas.h"')
    blob = hashlib.sha1(f'blob {len(source)}\0'.encode() + source).hexdigest()
    assert blob == expected, f'GitHub blob mismatch after normalising include paths: {name}'
print(f'Content matches NumWorks {m["release"]} at {m["commit"]}.')
