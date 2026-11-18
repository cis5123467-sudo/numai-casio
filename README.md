# NumAI for Casio Graph Math+

Revision notes, equation sheets, solvers and a CAS calculator in a native 396 × 224 Casio add-in. Current release: **v0.1.3**.

Download the .g3a from [Releases](https://github.com/cis5123467-sudo/numai-casio/releases/latest). Copy it to the root of the calculator's USB storage, eject the calculator, then launch NumAI from MPM's TOOLS add-ins menu. The target is **Graph Math+ OS 02.00.2202 with Math+ Mod (MPM)**. Back up your NumAI save files before replacing an existing installation.

## Revision and solving

- Edexcel IGCSE Mathematics, OCR Level 3 Additional Mathematics and Edexcel A level Mathematics, with worked examples.
- Separate AQA GCSE Biology, Chemistry and Physics courses, supporting explanations, specification references and Higher-only labels.
- Course search by all entered words, course name, reference, topic and note content. Equation search by names, symbols, units, topics and references.
- Physics and Chemistry equation sheets with variables and units, worked examples, use cases, rearrangements and subject-selecting solvers. Course cards link to related equations; fact sheets link back to the relevant topic.
- Unit conversion with a NumAI clipboard, formula rearrangement for the supplied Physics equations, a trigonometric equation solver and a triangle solver.
- Factorisation, simplification, solving for x, differentiation, integration, completing the square, factorials, stored variables and automatic closing parentheses.
- Exact fractions and roots where supported, decimal approximations, answer-format extras, and selectable decimal places from 0 to 10 (default 5).
- Named sessions, autosave, reusable calculation History, separate Physics and Chemistry favourites, and course favourites.

## Graph Math+ controls

| Physical key | NumAI action |
| --- | --- |
| CATALOG | Courses; press again in Courses to search |
| TOOLS | Equations and CAS; press again in equation menus to search |
| SHIFT + EXE | General NumAI menu |
| SETTINGS | Preferences |
| VARIABLE | Letter case, variables with stored values, and symbols |
| VARIABLE, RIGHT | Jump directly to symbols such as factorial !, =, >, < and _ |
| ALPHA + a red-letter key | Enter the letter printed on that physical key |
| SHIFT + ALPHA | Lock letters; ALPHA unlocks |
| ALPHA + decimal point / ×10^ | Space / double quote |
| SHIFT + 0, cursor keys, OK | Select text, then choose Copy or Cut |
| SHIFT + decimal point | Paste the NumAI clipboard |
| SHIFT + TOOLS | Favourite a topic/equation, or copy a supported result |
| SHIFT + x/θ/T | Insert the value-store arrow -> |
| SHIFT + ( | Equals |
| SHIFT + 7 / √ / x² / e^ | Pi / cube root / log / ln |
| SHIFT + sin / cos / tan | Inverse trigonometric functions |
| Fraction key / power key | Fraction / exponent entry |
| SHIFT + power key | Enter a change-of-base logarithm template |
| SHIFT + fraction key | Enter a mixed-number template |
| FORMAT | Additional answer formats for the selected/latest calculation |
| SHIFT + FORMAT | Ans, as labelled on Graph Math+ |
| ALPHA + FORMAT | Return to calculation home from any screen |
| AC / DEL | Clear the active input / delete a character or selection |
| SHIFT + DEL | Toggle insert and overwrite |
| Tab previous / next | Move through input fields or Home, Courses, Equations views |
| Page up / down | Scroll a page |
| CATALOG on an equation card | Open the related course topic |
| TOOLS on a topic card | Open related equations |
| BACK / HOME | Return / exit to the launcher |

ALPHA defaults to capitals, matching the printed red legends. Change to lowercase in VARIABLE when entering function names, searches or session names. The header shows SHIFT, ABC/abc, alpha lock, clipboard selection or overwrite status. The clipboard belongs to NumAI; it is not shared with other Casio applications.

This release binary uses the Graph Math+ Ans convention. For the documented fx-CG100 convention, build with NUMAI_MODEL=fxcg100: ALPHA + FORMAT inserts Ans and SHIFT + ALPHA + FORMAT returns home. That profile is source-selectable and is not the supplied Graph Math+ binary. Complex-number/polar entry, DMS entry, screen capture and Casio's native matrix/vector commands are outside NumAI's supported CAS operations.

## Display and saves

The interface uses the full 396 × 224 add-in display. It uses gint's native proportional colour font and its smaller index font, with transparent text backgrounds and measured bold spacing. The maths layout uses matching font heights, compact brackets, clear fraction-bar gaps, raised fractional exponents, and custom multiplication, pi and approximate-equality glyphs. Measurements and drawing share the same layout, including caret placement.

Sessions and preferences autosave to **numai.sav** in USB storage. NumAI keeps **numai.bak** and uses **numai.tmp** when replacing a save. Keep these files to retain work. Up to four named sessions are supported, reserving 10 KB each. Existing v0.1.1/v0.1.2 session records remain readable. Newly recorded solver History can reopen the original equation, unknown, inputs, units and angle mode. NumWorks-style Python records are stored inside the save file; the Casio port does not write into the Python app.

## Building

Install Python 3, the packages in requirements-dev.txt, SH GCC and a Math+-aware fxSDK/gint colour toolchain, then run:

    export CASIO_SDK=/path/to/toolchain/prefix
    python3 -m pip install -r requirements-dev.txt
    python3 tools/build.py

The result is release/numai-0.1.3.g3a. Build output goes to build/. The installed fxsdk command supplies include/library paths. The toolchain must provide fxconv, fxgxa, sh-elf-gcc, libgint-cg, fxlibc, OpenLibm and the colour linker script.

This release used SH GCC 15.2.0, fxSDK dev a6e46eb6, gint dev 463f180f, fxlibc dev b96335c2 and OpenLibm 9828d2e3. The existing Math+-aware toolchain includes its established startup adaptation. NumAI additionally normalises physical event positions for all five upper keyboard rows, correcting older gint event translations that cover only three rows. Both held and newly pressed keys consequently select the same app action.

## Testing

    export CASIO_EMULATOR=/path/to/emucasiocalc
    python3 tools/check_artifact.py
    python3 tools/native_controls.py
    python3 tools/smoke.py
    python3 tools/math_screens.py
    python3 tools/check_mpm.py /path/to/mpm-v1.1 release/numai-0.1.3.g3a

The native-controls host test requires a C compiler and the gint headers at CASIO_SDK's include path. The emulator scripts run the actual release G3A in emuCasioCalc's fx-CG50 model and save screenshots/logs to verification/. The original MPM C metadata/discovery functions are compiled by the MPM check. The historical save fixture contains a synthetic 5×5 calculation.

See [validation](docs/validation.md) and [release notes](RELEASE_NOTES.md). Emulator and packaging checks do not establish physical Graph Math+ compatibility. Physical testing of v0.1.3 is pending.

## Source and acknowledgements

Course content, search and solver History are ported from NumAI's NumWorks v0.1.2 source, commit c22d43b7fd1d408e2bb257a3c1cd7f679ebd743d. The seven shared content/catalogue files retain their verified byte-identical content. Casio rendering, input, packaging and save storage are adapted for this port.

Native fonts and rendering APIs come from gint by Lephenixnoir and contributors. Its upstream permission statement is preserved in vendor/gint/UPSTREAM-README.md. The bundled fxlibc printf implementation is CC0, with its license in vendor/fxlibc/LICENSE. Other toolchain components are installed dependencies rather than vendored source.
