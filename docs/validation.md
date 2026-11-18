# v0.1.3 validation

Release artifact: numai-0.1.3.g3a (562,624 bytes).

SHA-256: 9d1bf0769172cdbab8aa7367537956a245d7bfc115f7b4f704450c565f9d3c97

## Final artifact checks

- Actual release G3A executed in emuCasioCalc's fx-CG50 colour model.
- Startup, clean HOME exit, factorials, automatic closing parentheses, fraction results and reopening a saved session passed.
- CAS factorisation, Physics and Chemistry solvers, unit conversions, answer-format extras, Preferences, named sessions and older saves passed.
- Course search, equation search, related equation links, calculation-home shortcut and reusable solver History passed.
- Native ALPHA lock, Copy/Cut selection, paste, Graph Math+ Ans and FORMAT checks passed in the shared-key runtime flows.
- Host integration tests ran the production editor/handlers: A–Z, case selection, clipboard, overwrite, clear, store, cube roots, logarithms, Ans, home, SETTINGS, tabs and paging passed.
- Every position in the five upper Graph Math+ key rows was checked against an independently specified physical-key table. The compiled input bridge has the intended CATALOG, TOOLS, VARIABLE, FORMAT, SETTINGS, fraction, root, tab and page bindings.
- Selected/unselected icon payloads match the generated 92 × 64 images and leave the y=45 label region clear.
- MPM v1.1's actual C discovery and metadata functions recognise NumAI, version 00.01.0003 and both icon payloads.
- No credentials or local configuration files are tracked; build output, release assets, runtime saves and raw verification output are ignored. The deliberate historical save fixture is synthetic.

## Visual maths cases

The final artifact rendered all 24 cases without emulator faults. Both the editor and submitted calculation were captured. Representative screenshots are in this directory's screenshots folder.

    3*(1/2+2)*4
    2((1+2))*3
    1/2+3/4
    (1+2)/(3+4)
    1/(1+1/2)
    (2+3)^2
    2^(-3)
    2^(1/2)
    2^(3^2)
    (1/2)^2
    sqrt(2)+2*pi
    sqrt(1/2)
    (3+4)*(5-2)
    2*3*4
    1/3
    (1+2)^(-2/3)
    (2^3)^2
    (1/2)^(3/4)
    (1/(2+3))^(-2)
    1/2^2
    2^(-1/2)+3
    (1/2)^(-2)
    2^(123/456)
    (12/345)^(67/89)

The small fraction denominator has a clear gap below the fraction bar. Tall fractional exponents are raised separately from ordinary short exponents. Brackets use measured compact padding. Layout sizes and draw coordinates use the native 9-pixel and 7-pixel font metrics.

## Scope of verification

Target hardware is Graph Math+ OS 02.00.2202 with MPM. The emulator is an fx-CG50 model, so these are SuperH runtime and rendering checks, supplemented by native-key handler/table checks; they are not physical Graph Math+ verification. Testing on the physical Graph Math+ remains pending. The optional fx-CG100 modifier profile is supplied as a source build option, not the release binary.
