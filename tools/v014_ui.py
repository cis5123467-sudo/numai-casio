#!/usr/bin/env python3
"""Exercise the new v0.1.4 menu shortcuts and organic diagrams in the G3A."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import os
import subprocess

from PIL import Image

root = Path(__file__).resolve().parents[1]
output = root / "verification/v0.1.4"
emulator = os.environ.get("CASIO_EMULATOR", "/tmp/numplay-toolchain/emu-build/emucasiocalc")
addin = root / "release/numai-casio-v0.1.4.g3a"


def run(name, keys):
    folder = output / name
    folder.mkdir(parents=True, exist_ok=True)
    for old in folder.glob("*.png"):
        old.unlink()
    script = ", ".join(("scale 1", "wait 0.7s", *keys, "MENU"))
    result = subprocess.run([emulator, "--headless", "--model", "cg50", "--keys", script, addin],
                            cwd=folder, capture_output=True, text=True, timeout=90)
    log = result.stdout + result.stderr
    (folder / "run.log").write_text(log)
    assert result.returncode == 0 and "add-in exited after" in log and "stopped with an error" not in log, log
    return folder


def screen(folder, name):
    with Image.open(folder / (name + ".png")) as image:
        assert image.size == (396, 224)
        return image.convert("RGB")


def family(item):
    number, count = item
    keys = ["OPTN", "4", str(number)]
    for row in range(1, count + 1):
        keys.extend((str(row), "wait 0.35s", f"shot formula-{row}.png",
                     "EXE", "wait 0.55s", f"shot topic-{row}.png", "EXIT", "EXIT"))
    folder = run(f"organic-{number}", keys)
    diagrams = set()
    for row in range(1, count + 1):
        diagram = screen(folder, f"formula-{row}").crop((5, 48, 391, 148))
        # A structure has bond/atom pixels in this area and white margins.
        assert len(diagram.getcolors()) > 1
        assert diagram.getpixel((0, 0)) == (255, 255, 255)
        assert screen(folder, f"topic-{row}").tobytes() != screen(folder, f"formula-{row}").tobytes()
        diagrams.add(diagram.tobytes())
    assert len(diagrams) == count


def shortcuts():
    folder = run("menus", ["SHIFT", "EXE", "1", "wait 0.35s", "shot courses.png",
                           "EXIT", "OPTN", "2", "wait 0.35s", "shot physics.png",
                           "ALPHA", "XOT", "wait 0.35s", "shot alpha-a.png",
                           "EXIT", "0", "wait 0.35s", "shot second-group.png",
                           "1", "wait 0.35s", "shot group-entry.png"])
    gold = screen(folder, "courses").getpixel((5, 5))
    assert gold[0] > 240 and gold[1] > 190 and gold[2] < 25, gold
    assert len({screen(folder, name).tobytes() for name in
                ("courses", "physics", "alpha-a", "second-group", "group-entry")}) == 5


if __name__ == "__main__":
    with ThreadPoolExecutor(max_workers=3) as pool:
        shortcuts_result = pool.submit(shortcuts)
        list(pool.map(family, enumerate((5, 4, 4, 4, 1), 1)))
        shortcuts_result.result()
    print("All 18 molecule diagrams and linked notes, menu shortcuts and yellow-gold header passed.")
