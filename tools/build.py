#!/usr/bin/env python3
"""Build NumAI 0.1.3-r2 for Graph Math+ with the installed fxSDK/gint toolchain."""
from pathlib import Path
import os
import subprocess
import sys
from PIL import Image

root = Path(__file__).resolve().parents[1]
sdk = Path(os.environ.get("CASIO_SDK", "/tmp/numplay-toolchain/prefix"))
environment = {**os.environ, "PATH": str(sdk / "bin") + os.pathsep + os.environ["PATH"]}
def run(args):
    return subprocess.check_output(list(map(str, args)), cwd=root, env=environment, text=True).strip()
run([sys.executable, root / "tools/check_content_parity.py"])
include = Path(run(["fxsdk", "path", "include"]))
library = Path(run(["fxsdk", "path", "lib"]))
build = root / "build"
build.mkdir(exist_ok=True)
small = build / "casio-font.o"
run([sys.executable, sdk / "bin/fxconv", "-f", root / "assets/font5x7.png", "-o", small,
     "--cg", "--toolchain=sh-elf", "name:casio_small_font", "charset:ascii", "grid.size:5x7",
     "grid.padding:1", "grid.border:0", "line-distance:8"])
objects = [small]
for source in sorted((root / "src").glob("*.c")):
    output = build / (source.stem + ".o")
    run(["sh-elf-gcc", "-m4-nofpu", "-mb", "-nostdlib", "-fno-builtin", "-Os", "-std=gnu11",
         "-fdata-sections", "-ffunction-sections", "-fno-common", "-Wall", "-Wextra",
         "-DFXCG50", "-DPLATFORM_DEVICE=1", '-DNUMAI_VERSION="0.1.3-r2"',
         '-DNUMAI_FXCG100=' + ('1' if os.environ.get('NUMAI_MODEL') == 'fxcg100' else '0'),
         "-isystem", include, "-I", root / "src", "-c", source, "-o", output])
    objects.append(output)
elf = build / "NumAI.elf"
run(["sh-elf-gcc", "-m4-nofpu", "-mb", "-nostdlib", "-L", library, "-T", library / "fxcg50.ld",
     "-Wl,--gc-sections,-Map," + str(build / "NumAI.map"), *objects,
     "-Wl,--start-group", "-lgint-cg", "-lc", "-lopenlibm", "-lgcc", "-Wl,--end-group", "-o", elf])
raw = build / "NumAI.bin"
run(["sh-elf-objcopy", "-O", "binary", elf, raw])
logo = Image.open(root / "src/icon.png").convert("RGBA")
logo.thumbnail((40, 40), Image.Resampling.LANCZOS)
for selected, colour in [(False, "#ffffff"), (True, "#ffb52b")]:
    icon = Image.new("RGBA", (92, 64), colour)
    icon.alpha_composite(logo, ((92-logo.width)//2, (44-logo.height)//2))
    icon.convert("RGB").save(build / ("selected.png" if selected else "icon.png"))
(root / "release").mkdir(exist_ok=True)
release = root / "release/numai-0.1.3-r2.g3a"
run(["fxgxa", "--g3a", "--name=NumAI", "--internal=@NUMAI", "--version=00.01.0302",
     "--icon-uns=" + str(build / "icon.png"), "--icon-sel=" + str(build / "selected.png"),
     "-o", release, raw])
print(f"{release} — {release.stat().st_size:,} bytes")
