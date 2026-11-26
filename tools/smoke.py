#!/usr/bin/env python3
"""Run real SuperH add-in flows in emuCasioCalc's colour model."""
from pathlib import Path
from struct import unpack
import os
import subprocess
import tempfile
import shutil
from PIL import Image, ImageChops

root = Path(__file__).resolve().parents[1]
emulator = Path(os.environ.get("CASIO_EMULATOR", "/tmp/numplay-toolchain/emu-build/emucasiocalc"))
addin = root / "release/numai-casio-v0.1.4-r1.g3a"

def run(folder, script):
    folder.mkdir(parents=True, exist_ok=True)
    completed = subprocess.run([emulator, "--headless", "--model", "cg50", "--clock",
        "2026-11-17 12:00", "--keys", "scale 1, wait 0.7s, " + script.replace("shot ", "wait 0.5s, shot "), addin],
        cwd=folder, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=90)
    (folder / "run.log").write_text(completed.stdout)
    assert completed.returncode == 0 and "add-in exited after" in completed.stdout, completed.stdout
    assert "stopped with an error" not in completed.stdout
    return completed.stdout

def records(folder):
    data = (folder / "storage/fls0/numai.sav").read_bytes()
    position, output = 0, {}
    while length := unpack("<H", data[position:position+2])[0]:
        name, value = data[position+2:position+length].split(b"\0", 1)
        output[name.decode()] = value[1:-1].decode()
        position += length
    return output

base = Path(tempfile.mkdtemp(prefix="layout-release-", dir=root / "verification"))
print(f"Verification folder: {base}", flush=True)
factorial = "VARS, RIGHT, EXE, "
calc = base / "calculation"
run(calc, "shot startup.png, 5, " + factorial + "DIV, 2, " + factorial + "EXE, "
    "2, MULT, LPAR, 3, PLUS, 4, EXE, wait 0.5s, shot result.png, MENU")
text = records(calc)["session_default.py"]
assert "5!/2!" in text and "|60\n" in text and "2*(3+4)" in text and "|14\n" in text, text[:700]
run(calc, "shot restored.png, MENU")
assert ImageChops.difference(Image.open(calc/"result.png"), Image.open(calc/"restored.png")).getbbox() is None
print("Factorials, automatic parentheses, saved results and reopening passed", flush=True)

cas = base / "cas"
run(cas, "OPTN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, EXE, EXE, wait 0.4s, shot factorise.png, MENU")
assert "(x - 2)(x - 3)" in records(cas)["session_default.py"]
print("CAS factorisation passed", flush=True)

physics = base / "physics"
run(physics, "OPTN, DOWN, EXE, DOWN, EXE, EXE, EXE, 2, DOWN, 3, EXE, "
    "wait 0.4s, shot solver.png, MENU")
assert "Ek = 9 J" in records(physics)["session_default.py"]
print("Physics equation solver and autosave passed", flush=True)

sessions = base / "sessions"
run(sessions, "5, MULT, 5, EXE, SHIFT, EXE, DOWN, DOWN, EXE, 2, EXE, 1, DIV, 3, EXE, "
    "SHIFT, EXE, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, EXE, EXE, SHIFT, EXE, "
    "wait 0.4s, shot session2.png, MENU")
saved = records(sessions)
assert "25" in saved["session_default.py"] and "1/3" in saved["session_2.py"]
run(sessions, "shot restored.png, SHIFT, EXE, DOWN, DOWN, DOWN, EXE, shot sessions.png, UP, EXE, "
    "wait 0.3s, shot default.png, MENU")
assert ImageChops.difference(Image.open(sessions/"session2.png"), Image.open(sessions/"restored.png")).getbbox() is None
run(sessions, "shot default-restored.png, MENU")
assert ImageChops.difference(Image.open(sessions/"default.png"), Image.open(sessions/"default-restored.png")).getbbox() is None
print("Named sessions, preferences, switching and persistence passed", flush=True)

courses = base / "courses"
run(courses, "SHIFT, EXE, EXE, shot courses.png, DOWN, DOWN, EXE, EXE, EXE, EXE, "
    "wait 0.3s, shot topic.png, MENU")
assert ImageChops.difference(Image.open(courses/"courses.png"), Image.open(courses/"topic.png")).getbbox()
print("Course browser and topic content passed", flush=True)

menus = base / "menus"
run(menus, "SHIFT, EXE, shot menu.png, DOWN, DOWN, DOWN, DOWN, DOWN, EXE, "
    "shot shortcuts.png, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, "
    "shot shortcuts-scrolled.png, EXIT, DOWN, EXE, shot preferences.png, MENU")

chemistry = base / "chemistry"
run(chemistry, "OPTN, shot cas.png, DOWN, DOWN, EXE, shot equations.png, DOWN, EXE, "
    "shot facts.png, EXE, EXE, "
    "1, 2, DOWN, 6, shot form.png, EXE, shot result.png, MENU")
assert "N = 6" in records(chemistry)["session_default.py"]

converter = base / "converter"
run(converter, "OPTN, DOWN, DOWN, DOWN, DOWN, EXE, EXE, DOWN, DOWN, DOWN, EXE, DOWN, DOWN, DOWN, DOWN, EXE, "
    "2, 5, shot input.png, EXE, shot result.png, MENU")
assert "2.5 dm" in records(converter)["session_default.py"]

extras = base / "extras"
run(extras, "1, DIV, 3, EXE, UP, RIGHT, EXE, shot extra-results.png, MENU")

tools = base / "tools"
run(tools, "OPTN, DOWN, DOWN, DOWN, DOWN, DOWN, EXE, shot rearranger.png, EXE, "
    "shot rearranged.png, EXIT, EXIT, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, "
    "DOWN, DOWN, DOWN, DOWN, EXE, shot triangle.png, MENU")

# Load a save produced by the previous native-font release.
old = root / "tests/fixtures/v0.1.1.sav"
compatibility = base / "old-save"
(compatibility / "storage/fls0").mkdir(parents=True)
shutil.copyfile(old, compatibility / "storage/fls0/numai.sav")
run(compatibility, "shot old-session.png, MENU")
assert (compatibility / "storage/fls0/numai.sav").read_bytes() == old.read_bytes()

gold = (255, 182, 49)
for shot in (calc/"result.png", courses/"courses.png", menus/"menu.png", extras/"extra-results.png"):
    image = Image.open(shot).convert("RGB")
    assert image.size == (396,224), shot
    assert image.getpixel((0,0)) == image.getpixel((395,0)), shot
    assert image.getpixel((0,223)) == image.getpixel((395,223)), shot
print("Native screen bounds, menus, chemistry, conversions, extra results, and old saves passed", flush=True)

brackets = base / "brackets"
run(brackets, "3, MULT, LPAR, 1, DIV, 2, PLUS, 2, RPAR, MULT, 4, "
    "shot tall-input.png, LEFT, LEFT, shot cursor-in-group.png, EXE, "
    "2, LPAR, LPAR, 1, PLUS, 2, RPAR, RPAR, MULT, 3, EXE, shot grouped-history.png, MENU")
saved = records(brackets)["session_default.py"]
assert "3*(1/2+2)*4" in saved and "|30" in saved
assert "2((1+2))*3" in saved and "|18" in saved
print("Bracket spacing, fraction groups, nested groups and cursor navigation passed", flush=True)

search = base / "search"
run(search, "SHIFT, EXE, EXE, DOWN, EXE, ALPHA, SQUARE, ALPHA, 8, ALPHA, SQUARE, "
    "ALPHA, 6, ALPHA, COMMA, ALPHA, MINUS, shot query.png, shot results.png, "
    "EXE, shot selected-topic.png, EXIT, shot returned-results.png, MENU")
assert ImageChops.difference(Image.open(search/"results.png"), Image.open(search/"returned-results.png")).getbbox() is None
print("Course search, opening a result, and returning to results passed", flush=True)

equation_search = base / "equation-search"
run(equation_search, "OPTN, OPTN, ALPHA, 7, ALPHA, 9, ALPHA, RPAR, "
    "shot mol-results.png, EXE, shot equation.png, ALPHA, FD, shot home-shortcut.png, MENU")
assert Image.open(equation_search/"home-shortcut.png").getpixel((0,0)) == Image.open(calc/"result.png").getpixel((0,0))

related = base / "related"
run(related, "SHIFT, EXE, EXE, DOWN, EXE, 4, DP, 1, DP, 1, DP, 2, shot spec-results.png, "
    "EXE, shot topic-related.png, OPTN, shot related.png, EXE, shot equation.png, "
    "EXIT, EXIT, shot back-topic.png, ALPHA, FD, shot home.png, MENU")

reuse = base / "reuse"
run(reuse, "OPTN, DOWN, EXE, DOWN, EXE, EXE, EXE, 2, DOWN, 3, EXE, "
    "ALPHA, FD, SHIFT, EXE, DOWN, DOWN, DOWN, DOWN, EXE, EXE, shot history.png, "
    "EXE, shot reuse-form.png, EXE, shot reused-result.png, MENU")
saved = records(reuse)["session_default.py"]
assert "Ek = 9 J" in saved and "# R|" in saved, saved[:1800]
run(reuse, "SHIFT, EXE, DOWN, DOWN, DOWN, DOWN, EXE, EXE, EXE, "
    "shot restored-inputs.png, MENU")
assert ImageChops.difference(Image.open(reuse/"reuse-form.png"), Image.open(reuse/"restored-inputs.png")).getbbox() is None
print("Live equation search, related equations, Alpha+ANS and saved History reuse passed", flush=True)

# Native shared physical keys exercise the shipped binary through gint.
native = base / "native-keyboard"
run(native, "SHIFT, ALPHA, 7, 9, RPAR, shot locked.png, ALPHA, AC, "
    "1, 2, 3, SHIFT, 0, LEFT, LEFT, EXE, shot clipboard.png, EXE, RIGHT, "
    "SHIFT, DP, shot pasted.png, EXE, SHIFT, FD, PLUS, 1, EXE, "
    "SHIFT, LPAR, shot equals.png, AC, SHIFT, 7, EXE, FD, shot format.png, MENU")
saved = records(native)["session_default.py"]
assert "12323" in saved and "12324" in saved and "pi" in saved, saved[:1500]
print("Native alpha lock, clipboard selection/paste, SHIFT+FORMAT Ans, pi and FORMAT extras passed", flush=True)
