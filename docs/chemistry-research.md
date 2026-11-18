# Chemistry research and source parity for v0.1.3-r1

Checked 18 November 2026. This revision follows **AQA GCSE Chemistry 8462 (separate Chemistry)**. Original explanations, numerical examples and revision prompts were added for all existing Chemistry cards. The specification establishes coverage and tier boundaries; it is not reproduced as textbook text.

## NumWorks release compared

The GitHub connector confirmed release 0.1.2-r1 and source commit **96245a14873751dc4484102dff67cdc768c4ac1e** in cis5123467-sudo/numai. The commit comparison with c22d43b7fd1d408e2bb257a3c1cd7f679ebd743d identified the Chemical Changes expansion, its new Key Ideas entry, science emphasis terms, the COURSES header, and the CALCULATION home title. The other changed files concern the NumWorks build, tests, queue and personal instructions.

The exact source catalogue from that revision is pinned in data/aqa_catalog_numworks_0.1.2-r1.inc. The generator keeps its notes and appends original topic-specific material from data/chemistry_revision.json. Biology and Physics catalogue sections remain unchanged. The shared scientific-skills cards remain unchanged for those courses; Chemistry has its own expanded variants. NumWorks ARM packaging and keyboard handling are replaced by the established Casio implementations.

## Coverage

| Section | Cards including overview | Individual Key ideas views |
| --- | ---: | ---: |
| Atomic structure and periodic table | 17 | 16 |
| Bonding and properties | 20 | 19 |
| Quantitative chemistry | 17 | 16 |
| Chemical changes | 18 | 18 |
| Energy changes | 7 | 6 |
| Rate and extent of change | 13 | 12 |
| Organic chemistry | 14 | 13 |
| Chemical analysis | 15 | 14 |
| Atmosphere | 11 | 10 |
| Using resources | 13 | 12 |
| Chemistry key ideas | 1 | 1 |
| Required practicals | 10 | 9 |
| Scientific and mathematical skills | 6 | 5 |
| Total | 162 | 151 |

Every individual card has a separate Key ideas view opened with OK or EXE; press it again for full notes. BACK from Key ideas returns to full notes. Each section also begins with a summary, including the existing Chemical Changes and overarching Chemistry Key Ideas entries. These are revision summaries and are not extra specification requirements.

## Primary specification references

- [Subject content and tier conventions](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content)
- [Atomic structure and periodic table](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/atomic-structure-and-the-periodic-table)
- [Bonding, structure and properties](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/bonding-structure-and-the-properties-of-matter)
- [Quantitative chemistry](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/quantitative-chemistry)
- [Chemical changes](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/chemical-changes)
- [Energy changes](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/energy-changes)
- [Rates and equilibrium](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/the-rate-and-extent-of-chemical-change)
- [Organic chemistry](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/organic-chemistry)
- [Chemical analysis](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/chemical-analysis)
- [Atmosphere](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/chemistry-of-the-atmosphere)
- [Using resources](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/using-resources)
- [Key ideas](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/subject-content/key-ideas)
- [Working scientifically](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/working-scientifically)
- [Mathematical requirements](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/mathematical-requirements)
- [Practical assessment, including all eight required practicals](https://www.aqa.org.uk/subjects/chemistry/gcse/chemistry-8462/specification/practical-assessment)

Higher-only cards retain their labels. Mixed-tier summaries explicitly mark Higher-only material such as mole calculations, electron-transfer equations, weak-acid ionisation, bond-energy calculations, equilibrium predictions, condensation polymers and alternative extraction. Separate-Chemistry content remains included even where it is absent from Combined Science.

## Supporting primary educational resources

Royal Society of Chemistry resources were used to check practical reasoning and interpretation:

- [Preparing a soluble salt](https://edu.rsc.org/practical/preparing-a-salt-practical-videos-14-16-students/4011982.article)
- [Simple titration](https://edu.rsc.org/concentration-of-solutions-and-titration/simple-titration-practical-videos-14-16-students/4011981.article)
- [Electrolysis of solutions](https://edu.rsc.org/experiments/the-electrolysis-of-solutions/466.article)
- [Electrolysis of brine](https://edu.rsc.org/experiments/electrolysis-of-brine/735.article)
- [Chromatography](https://edu.rsc.org/resources/chromatography/11333.article)
- [Identifying ions](https://edu.rsc.org/practical/identifying-ions-practical-videos-14-16-students/4011491.article)
- [Simple distillation](https://edu.rsc.org/separating-mixtures/simple-distillation-practical-videos-14-16-years/4018538.article)

Definitions, examples and calculations in the new dataset are original revision material. The sources above record the coverage and practical checks used for this revision.

## Regenerating and checking

    python3 tools/generate_chemistry.py
    python3 tools/native_controls.py chemistry_content
    python3 tools/chemistry_screens.py

Generation rejects missing or unmatched topic titles. The production-content test visits all cards, checks key-view navigation and related links, searches newly added terms, and tests full text against the fixed reader capacity. Actual font rendering and keypad navigation are checked separately in the release G3A using emuCasioCalc. See the release validation report for results and hardware limits.
