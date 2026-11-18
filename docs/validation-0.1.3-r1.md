# v0.1.3-r1 validation

Artifact: numai-0.1.3-r1.g3a, 703,216 bytes.

SHA-256: 77153687d228b9db081d8bc47539c95cf799ff6a85eade537661c8688fdf8103

## Content and source checks

- Compared the requested NumWorks release 0.1.2-r1 through the GitHub connector and pinned its exact source catalogue at commit 96245a14873751dc4484102dff67cdc768c4ac1e.
- Independent compiled comparison preserves all 151 original Chemistry entries with their original notes and supporting text. Biology and Physics catalogue contents remain unchanged.
- Added 151 individual topic expansions and separate Key ideas texts. The Chemistry browser contains 162 cards across 13 sections, including the summaries.
- Production-handler checks open every card, toggle Key ideas/full notes, return with BACK, find related equations and search newly added content.
- A conservative content-capacity check reaches at most 78 wrapped lines, below the reader's 240-line capacity; no card text is truncated by that limit.
- Generator checks reject missing or unmatched topic data. The build regenerates the catalogue from the pinned source and editable JSON.

## Final G3A runtime checks

The actual release G3A was executed in emuCasioCalc's fx-CG50 colour model. All 162 Chemistry cards, their scroll views and the 151 separate Key ideas views passed. Scripts run in batches below the emulator's 512-step limit and allow complete page redraws between physical key events. Representative screenshots are in docs/screenshots/0.1.3-r1; raw logs and captures are generated under verification/.

Regression checks passed for factorials, automatic brackets, CAS factorisation, Physics/Chemistry solvers, units, course and equation search, related links, reusable History, preferences, named sessions, old saves, clipboard operations, alpha lock, Ans and FORMAT.

All 24 bracket, fraction, radical, symbol and power rendering cases passed again. Native-key handler and compiled physical-key mapping checks passed. G3A/icon dimensions and payload checks passed. MPM v1.1's actual discovery/metadata code recognised NumAI version 00.01.0301 and both icon blocks.

Scrolling reuses an unchanged reading layout; changing page, topic or text invalidates it. Key ideas views omit the longer supporting paragraph appended to the full notes.

## Hardware limits

Target: Graph Math+ OS 02.00.2202 with MPM. Physical calculator verification remains pending. An fx-CG50 emulator cannot establish the behaviour of the exact Graph Math+ display and keyboard hardware; native physical-row mappings are checked separately in host and compiled-table tests.
