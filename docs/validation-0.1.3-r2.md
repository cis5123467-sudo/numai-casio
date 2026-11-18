# v0.1.3-r2 validation

Artifact: numai-0.1.3-r2.g3a, 637,612 bytes.

SHA-256: 53d6ab1bf78a0b7b17cf3aed7827e4e4ca914be63e2791c760b3fd716e9880af

## Exact NumWorks content

The newest NumWorks release was confirmed as 0.1.3 at commit 0cedcddede9cf3e756ecd0508cf362cfb1d3ce4c, and checked again before publication. Nine delivered curriculum/equation/unit source files match both the GitHub Git-blob hashes and SHA-256 hashes. Every build runs this verification.

Chemistry was checked separately: all 151 entries match the pinned reference in chapter order, titles, notes, supporting text, examples and Higher-only labels. The same Chemistry equation source supplies all 29 sheets, including equations, units, examples, uses, rearrangements and solver data. Physics, Biology and extended maths content come from the same exact shared source files. There are no Casio-only Chemistry notes or extra Key ideas views in this revision.

The independently compiled reference catalogue agrees with all science course entries. All 129 Physics entries match, with Key Ideas first in the eight main chapters. Production navigation checks open the notes, resolve related equations and stay within the fixed reader capacity. All 64 Physics/Chemistry equation-sheet return links resolve to the matching topic reference. Maximum conservative wrapped lengths are 62 lines for Physics and 61 for Chemistry, below the 240-line limit.

## Final G3A runtime and display

The actual release G3A ran in emuCasioCalc's fx-CG50 colour model. All 129 Physics entries and all 151 Chemistry entries were opened and scrolled. Screenshot headers remain stable during scrolling. Scripts are batched below the emulator's 512-step limit. Representative screenshots are in docs/screenshots/0.1.3-r2.

The calculator/history checks confirm a 396 × 224 screen and a white bottom edge without the old routine footer. The production drawing harness separately verifies that an exceptional status message still displays a footer. Courses opens Search topics from its second entry.

Unit screenshots cover squared and cubed selectors and density headings with literal slashes. Runtime numerical checks include 25000 cm^2 -> 2.5 m^2, 2500 cm^3 -> 2.5 dm^3, and 2.5 g/cm^3 -> 2500 kg/m^3. The production painter confirms raised digits and a literal slash, with no fraction bar for compound unit separators.

Regression checks pass for factorials, automatic brackets, CAS factorisation, Physics/Chemistry solvers, unit conversion, course/equation search, related links, reusable History, named sessions, Preferences, older saves, alpha lock, clipboard operations, Ans and FORMAT. All 24 bracket/fraction/root/symbol/power cases pass again.

Presentation-only checks preserve spaces around short connecting words beside typeset units. Stored curriculum and equation strings remain byte-identical. Reader layout caching and a fast preliminary width pass reduce long-note rendering work without changing stored content.

G3A package size/icons and the compiled physical-key table pass. MPM v1.1's actual discovery and metadata code recognises NumAI version 00.01.0302 and both icon payloads. The earlier r1 and v0.1.3 release binaries are retained.

## Hardware limits

Target: Graph Math+ OS 02.00.2202 with MPM. Physical calculator testing remains pending. The fx-CG50 emulator cannot establish exact behaviour on the physical Math+ keyboard, display or OS; native physical-row mappings are checked separately.
