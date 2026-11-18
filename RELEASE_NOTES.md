# NumAI Casio v0.1.3-r2

This revision ports the newest NumWorks release, v0.1.3, to Graph Math+ OS 02.00.2202 with MPM. All course notes, topics, methods, worked examples, equations and unit definitions now match the NumWorks release exactly.

## Exact content parity, including Chemistry

- Pinned NumWorks source commit 0cedcddede9cf3e756ecd0508cf362cfb1d3ce4c, the published 0.1.3 release.
- Matched all nine shared content source files byte-for-byte: topics.c, topics.h, aqa_catalog.inc, maths_details.inc, physics.c, physics.h, chemistry.c, units.c and units.h.
- Checked both GitHub Git-blob hashes and SHA-256 hashes. The build now rejects changes that would silently diverge from the pinned content.
- Chemistry has the same 151 course entries, chapter order, titles, Higher-only labels, notes, supporting text and examples as NumWorks. This includes the complete earlier Chemical Changes expansion and its Key Ideas card.
- All 29 Chemistry equation fact sheets retain exactly the same equations, symbol descriptions, units, use cases, examples, rearrangements and solver data as NumWorks. All 35 Physics equation sheets and the extended maths content are also identical.
- The additional Chemistry notes, section cards and individual Key ideas views introduced only in Casio r1 are removed from the r2 app to meet the requested exact content match. The r1 release and its source tag remain available.

## Physics revision from NumWorks v0.1.3

- Imported all rewritten and expanded Physics notes: 124 Physics entries plus five shared science-skills entries, giving 129 entries in the Physics course.
- Key Ideas is first in all eight main chapters: Energy, Electricity, Particle model, Atomic structure, Forces, Waves, Magnetism and electromagnetism, and Space physics.
- Topic-specific explanations include worked substitutions, conversions, answers/units, rearrangements, graph interpretation, practical methods, controls, uncertainty and common exam mistakes.
- Coverage includes gravitational/kinetic/elastic energy, heating and latent heat, component characteristics, circuits and power, National Grid and transformers, density and gases, radiation and half-life, forces, waves, magnetism and space.
- Preserved separate-Physics extensions and all Higher-only labels, including the distinction between ideal-transformer power and turns-ratio requirements.
- Imported the extra emphasis terms and headings while retaining the native Casio fonts and previously corrected bracket, fraction and power rendering.

## Calculation, Courses and units

- Removed routine shortcut footer text from Calculation and its selected-history view. The editor and calculation area extend to the bottom of the native 396 × 224 screen.
- Exceptional status messages still reserve footer space, including save warnings.
- Courses keeps Favourites first and Search topics second, followed by the courses, matching the new NumWorks order. CATALOG again opens search.
- Unit selectors and conversion headings now typeset squared/cubed units with raised powers. Compound units retain literal slash separators, for example kg/m³.
- Unit factors, numerical results, expression entry and SHIFT + TOOLS copy-number behaviour are unchanged.
- Preserved prose spaces around words such as "in" and "to" beside typeset quantities and units; the curriculum strings are unchanged.
- Long-note wrapping uses a fast initial font-width pass followed by exact formatted-width checks. The existing reader-layout cache keeps scrolling responsive; this changes presentation work without editing the stored notes.

## Casio controls and saved work

CATALOG opens Courses, TOOLS opens Equations and CAS, SHIFT + EXE opens the general menu, and ALPHA + FORMAT returns to Calculation. Existing native Casio modifier mappings and topic/equation links are retained.

Copy numai-0.1.3-r2.g3a to the root of USB storage, eject safely, then launch NumAI through MPM's TOOLS add-ins menu. Preserve numai.sav and numai.bak to keep named sessions. Save formats and allocations are unchanged.

## Validation

Checks cover exact shared-source hashes, every Physics and Chemistry course entry, equation links, reader capacity, calculator footer/status behaviour, raised-unit selectors and headings, conversions, search, reusable History, sessions, CAS and native key handling. The existing 24 bracket/fraction/power regression cases are rerun against the final G3A. MPM discovery and package/icon metadata are checked separately.

Runtime checks use emuCasioCalc's fx-CG50 colour model. Physical Graph Math+ verification remains pending; the emulator cannot establish exact hardware/display/keyboard behaviour on the physical target.

---

# NumAI Casio v0.1.3-r1

This revision imports the complete NumWorks v0.1.2-r1 Chemistry update, expands every Chemistry topic, and adds quick Key ideas views alongside the detailed notes. It targets Graph Math+ OS 02.00.2202 with MPM.

## NumWorks release parity

Compared the published NumWorks 0.1.2-r1 release and commit 96245a14873751dc4484102dff67cdc768c4ac1e against the previous v0.1.2 source.

- Retained the Chemical Changes Key Ideas entry with all ten quick facts and the four acid reaction patterns.
- Imported all 17 expanded Chemical Changes pages, including the reactivity series with aluminium, cold-water and dilute-acid reactions, displacement, oxygen/electron redox definitions and half equations.
- Preserved the expanded acid/base/alkali definitions, salt naming, neutralisation, indicator/pH explanations and carbonate gas tests.
- Imported the full copper sulfate preparation and crystallisation method, its explanations, titration technique, concordant-titre mean and Higher-only calculation examples, including the 0.0800 mol/dm^3 example and mass-concentration conversion.
- Retained strong/weak versus concentrated/dilute explanations, pH factors, molten/aqueous electrolysis predictions, gas tests, practical variables, Higher-only electrode equations, cryolite and carbon-anode replacement.
- Added the upstream science-emphasis terms, retained the COURSES title, and changed the centred gold calculation header to CALCULATION.
- Kept the existing Casio key mappings, USB sessions, icon dimensions and maths-rendering fixes.

## Expanded Chemistry throughout

- 151 original topic-specific additions across all 13 Chemistry sections, giving 162 cards including section summaries.
- A separate Key ideas view for each of the 151 individual entries. Press OK or EXE while reading to switch between Key ideas and the full notes; BACK from Key ideas returns to the full notes.
- A summary at the start of each section, including the existing Chemical Changes and overarching Chemistry summaries. New summaries cover atomic structure, bonding, quantitative work, energy, rates/equilibrium, organic chemistry, analysis, atmosphere, resources, practicals and scientific skills.
- Detailed explanations tie observations to particle, electron, bonding or energy models. Worked applications include isotope averages, formula masses, equation balancing, percentages, mole ratios, limiting reactants, titrations, gas volumes, bond energies, graph gradients, chromatography and alloy composition.
- Added practical reasoning for salt preparation, titration, electrolysis, calorimetry, reaction-rate investigations, chromatography, ion identification and water purification. Notes explain apparatus choices, controls, observations, uncertainty and common mistakes.
- Expanded structure/property comparisons, nanoparticles, hydrocarbons and functional groups, polymerisation, gas/ion tests, instrumental analysis, atmospheric processes, emissions, water treatment, extraction, life-cycle assessment, materials, Haber conditions and NPK fertilisers.
- Higher-only cards keep their existing labels, and mixed-tier summaries explicitly identify Higher-only material.
- Search includes all new explanations and Key ideas. TOOLS links to related Chemistry equations remain available from either reading view.
- Cached the unchanged reader layout so scrolling long notes no longer recalculates every wrapped line on every redraw.

## Sources and maintainability

Coverage and tier boundaries were checked against all AQA 8462 subject-content sections, required practicals, working-scientifically and mathematical requirements. Royal Society of Chemistry resources support the practical checks. The additions contain original explanations and examples; the source record and coverage table are in docs/chemistry-research.md.

The exact NumWorks source catalogue is pinned in data/. The new material is editable JSON, and tools/generate_chemistry.py validates complete topic coverage before generating the catalogue. The build invokes the generator automatically. An independent content test checks all 151 upstream Chemistry entries remain present with their original notes and supporting text, and keeps Biology/Physics catalogue content unchanged.

## Installation and saved work

Copy numai-0.1.3-r1.g3a to the root of USB storage, eject safely and launch from MPM's TOOLS add-ins menu. Keep numai.sav and numai.bak to retain named sessions. Existing save formats and allocations are unchanged.

## Verification

- Production-content checks cover all 162 cards, 151 Key ideas views, 13 section summaries, related equations, search and fixed-reader capacity.
- The final SuperH G3A is exercised in emuCasioCalc's fx-CG50 colour model, covering every Chemistry card, its separate Key ideas view and scrolling.
- Regression checks cover CAS, Physics/Chemistry equation solving, conversions, search, reusable History, named sessions, preferences, older saves, native modifier/clipboard controls and the 24 bracket/fraction/power rendering cases from v0.1.3.
- G3A/icon metadata and MPM v1.1 discovery checks are included.

Physical Graph Math+ testing remains pending. The fx-CG50 emulator and native-key handler tests cannot establish compatibility on the exact physical Math+ hardware.

---

# NumAI Casio v0.1.3

This release brings the queued MPM icon and Graph Math+ keyboard changes to the Casio port, and fixes the requested maths display issues before publication. It also publishes the complete current Casio source in its own repository.

## New changes since v0.1.2 revision 2

### Maths layout: brackets, fractions, powers and symbols

- Use the actual 9-pixel normal font and 7-pixel index font heights instead of the old NumWorks layout heights. Numbers, operators, fraction bars and bracket curves now share a consistent mathematical axis.
- Replace excessive bracket padding with compact measured spacing. Ordinary brackets use the native font; brackets around fractions and other tall groups stretch without touching the contents.
- Keep a clear gap between the fraction bar and numerator/denominator. This also applies to the small fractions used inside powers, where the denominator previously sat against the bar.
- Raise fractional powers further than simple exponents, so the denominator clears the base. Preserve explicit grouping for a fraction raised to a power, a fractional exponent, negative exponents and nested powers.
- Add consistent spacing between neighbouring layout runs and binary operators, while measuring the same spacing used for drawing.
- Align multiplication, pi and approximate-equality glyphs within their measured bounds. Mixed text/symbol runs retain the font's character spacing.
- Fit long fallback expressions using measured proportional widths instead of old fixed-width assumptions.

### Native Graph Math+ keyboard

- Replace inherited NumWorks ALPHA letter order with the actual Casio red A–Z legends. ALPHA + x/θ/T enters A, ALPHA + fraction enters B, ALPHA + square root enters C, and the remaining keys follow the physical keypad.
- ALPHA enters one letter. SHIFT + ALPHA locks alphabetic entry; ALPHA unlocks. VARIABLE offers uppercase/lowercase selection, stored variable values and additional symbols. RIGHT jumps directly from variables to symbols for quick factorial, equality and inequality entry.
- Restore printed SHIFT operations for pi, cube root, log, ln, inverse trig, brackets, equality, negative sign and storage. The dedicated fraction and power keys enter fractions and powers; shifted versions offer mixed-number and change-of-base-logarithm templates.
- SHIFT + FORMAT inserts Ans on Graph Math+. FORMAT opens answer-format extras. ALPHA + FORMAT returns to calculation home. An optional fx-CG100 source profile accounts for that model's different Ans modifier.
- SETTINGS opens Preferences; AC clears the active input; DEL deletes; SHIFT + DEL toggles insertion/overwrite. The tab keys navigate fields/views instead of entering an imaginary unit. Page keys scroll a page.
- Implement Casio-style clipboard selection: SHIFT + 0, cursor movement, OK, then Copy or Cut. SHIFT + decimal point pastes. Selection status appears in the header. The clipboard is internal to NumAI.
- Preserve CATALOG for Courses, TOOLS for Equations and CAS, SHIFT + EXE for the general menu, SHIFT + TOOLS for favourites, and both directions of topic/equation navigation.
- Correct the event/held-state disagreement in older Math+-aware gint builds by normalising all five upper physical rows. This covers the function keys that older event translation left as legacy fx-CG50 codes.
- Update the shortcut table, tooltips and documentation to the new bindings, with small native-style mathematical key glyphs.

### MPM icon

- Generate both selected and unselected icons at MPM's required 92 × 64 dimensions.
- Place the 40 × 40 logo in the upper 44-pixel area, leaving the app-name overlay at y=45 clear. Preserve its aspect ratio and centre it horizontally.

## Features included from the existing Casio port

- Full-screen native layout, readable proportional Casio fonts, transparent text backgrounds, bold science terms, maths superscripts/subscripts and two-dimensional fractions/roots.
- Edexcel IGCSE Mathematics, OCR Additional Mathematics, Edexcel A level Mathematics, and separate AQA GCSE Physics, Chemistry and Biology courses, with specification references, revision explanations, worked examples and Higher-only labels.
- Live course search across titles, courses, codes and notes. Live Physics/Chemistry equation search across names, symbols, units, topics and references. Queries match all entered words without case sensitivity and return up to 64 matches, with a refinement prompt for larger lists.
- Related equations below a topic's specification reference; TOOLS opens them. CATALOG on a fact sheet opens the relevant course topic.
- AQA Physics and Chemistry equation sheets, with word/symbol equations, symbol meanings, units and long unit names, worked examples, applications, rearrangements and equation solvers. Solvers show the chosen rearrangement, substituted values and units in the result.
- Physics formula rearrangement, trigonometric equation and triangle solvers, and Physics/Chemistry unit conversion with copyable numerical results.
- CAS operations including factorise, simplify, solve for x, differentiate, integrate and complete the square. Includes factorials, automatic bracket completion, stored variables, exact fractions/roots where supported and decimal approximations.
- General menu containing Courses, Equations and CAS, New Session, Open Session, History, Keyboard Shortcuts, Preferences and About.
- Up to four named sessions, automatic saving, reopening the previous session, separate course/Physics/Chemistry favourites, reusable solver History, and compatibility with existing session records.
- Decimal-place preference from 0 to 10, default 5; angle preference defaults to degrees.

## Installation and saved work

Copy numai-0.1.3.g3a to the root of USB storage, safely eject, then launch NumAI through MPM's TOOLS add-ins menu. Keep numai.sav and numai.bak when upgrading. NumAI uses numai.tmp during save replacement. Casio saves are USB files; this port does not create scripts in Casio's native Python application.

## Validation and limits

The final G3A is executed in emuCasioCalc's colour fx-CG50 model. Runtime checks cover launch/exit, factorials, automatic parentheses, CAS factorisation, Physics and Chemistry solving, conversions, named sessions, preferences, reopening saves, old-session migration, course/equation search, related links, reusable History, clipboard operations, alpha lock, Ans and FORMAT.

Twenty-four dedicated visual cases cover ordinary/tall/nested brackets, simple/nested fractions, positive/negative/nested powers, fractional exponents, powers of fractions, multi-digit fractions in exponents, roots, pi, multiplication and approximate results. Screenshots are retained by the test scripts and representative results are included in docs/screenshots.

Host integration tests exercise the production editor and handlers for the complete physical alphabet, case selection, copy/cut/paste, insertion/overwrite, clear, storage, cube roots/logarithms, Ans, home, settings, tabs and paging. The physical-row mapping and compiled key table are checked independently. G3A dimensions, icon payloads and MPM v1.1 discovery/metadata checks pass.

Target: Graph Math+ OS 02.00.2202 with MPM. The fx-CG50 emulator cannot establish physical Graph Math+ compatibility or exercise its exact keyboard hardware; physical testing of this release remains pending. NumAI is a school-maths CAS, not a complete implementation of Casio's native matrix/vector, complex/polar, DMS or screenshot commands.
