# NumWorks content parity in Casio v0.1.3-r2

Source: cis5123467-sudo/numai, published release 0.1.3, commit 0cedcddede9cf3e756ecd0508cf362cfb1d3ce4c.

The GitHub connector retrieved the latest release, compared it with the previous source, and supplied the Git tree hashes used for verification. Local files were copied from that exact commit.

The following delivered files are byte-identical to NumWorks:

- src/topics.c and src/topics.h: courses, chapters, topics, methods, formula-based tools and their default inputs.
- src/aqa_catalog.inc: every AQA Physics, Chemistry and Biology note, title, specification reference, Higher-only label, supporting explanation and chapter order.
- src/maths_details.inc: extended maths notes and worked examples.
- src/physics.c and src/physics.h: Physics equation sheets and shared equation/solver definitions.
- src/chemistry.c: all Chemistry equation sheets and their symbols, units, examples, uses, rearrangements and solver data.
- src/units.c and src/units.h: every unit label, factor, offset, group and conversion implementation.

The manifest in data/numworks-0.1.3-parity.json records both SHA-256 and GitHub Git-blob hashes. tools/check_content_parity.py checks all nine files at every build. This separately verifies the Chemistry catalogue and Chemistry equation file, not just aggregate topic counts.

The Physics course exposes 129 entries: 124 Physics entries and five shared scientific-skills entries. Chemistry exposes the same 151 entries as the NumWorks release, including the original Chemical Changes Key Ideas card. Casio-only r1 Chemistry extensions and per-card Key ideas views are absent from r2. Historical r1 content remains in its Git tag and release.

The Casio platform layer adapts screen geometry, fonts, physical key names, MPM packaging and USB saves. Mathematical layout can wrap differently on the wider Casio screen; the underlying curriculum strings and equation data are identical. Related-equation navigation and fact-sheet return links resolve the shared specification references.

Verification combines byte-level checks, an independent compiled reference catalogue, production navigation/content-capacity checks and real SuperH emulator runs. See docs/validation-0.1.3-r2.md for the final artifact and results.
