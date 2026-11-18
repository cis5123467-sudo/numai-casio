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
