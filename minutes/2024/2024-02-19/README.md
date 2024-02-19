## Meeting details

Date: 2024-02-14
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1NddUrkHPJukhUo8OeD7uvrWCqRaMt9zx/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2024-JAN-08](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-08), [2024-JAN-22](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-22), [2024-FEB-05](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-05)
- Current meeting: [2024-FEB-19](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-19)
- Next meeting: 2024-MAR-04

## Agenda
- [Zoom recording]()
- AME meeting schedule.
- IME meeting schedule. (Same time as the Vector SIG meeting, alternating weeks.)
- Vector SIG meeting on February 19th, President's Day.
- Developments in the matrix extensions work.

## Integrated Matrix Extensions (IME) Task Group resources
- [Groups.io](https://lists.riscv.org/g/tech-integrated-matrix-extension)
- [Github](https://github.com/riscv-admin/integrated-matrix-extension)
- [Zoom](https://zoom.us/j/93397157767?pwd=UE0vbWJEU0dFSXR4dlp5NGZjaUJJdz09) Meeting ID: 933 9715 7767, Passcode: 051351
- Guido Araujo is the acting chair for the IME TG.
- Jose Moreira is the acting vice-chair for the IME TG.

## SiFive matrix extensions
The following SiFive matrix extensions are documented in their [website](https://www.sifive.com/documentation), under "SiFive Intelligence Extensions":
- [SiFive Int8 Matrix Multiplication Extensions Specification](https://sifive.cdn.prismic.io/sifive/60d5a660-3af0-49a3-a904-d2bbb1a21517_int8-matmul-spec.pdf)
- [Matrix Multiply Accumulate Instruction (Xsfvfwmaccqqq) Extension Specification](https://sifive.cdn.prismic.io/sifive/c391d53e-ffcf-4091-82f6-c37bf3e883ed_xsfvfwmaccqqq-spec.pdf)
These SiFive matrix extensions fall in our "Option C: Multiple matrices in one vector register." To be more precise, multiple *matrix tiles* can fit in a single vector register.

## Next work items for Vector SIG
- We expect many of the members in RISC-V Vector SIG to participate in the IME and AME TGs.
- We will organize regular updates from the IME TG, to be presented at the regular Vector SIG meetings.
- Continue to investigate and explore sparsity support for matrix computations with RISC-V. Goals are (1) to provide a sanity check for the active matrix extension activities, so that they do not preclude future extensions with sparsity support, and (2) feed into future vector extensions activities that will spec sparsity support.
- Self-contained vector instructions (likely with 64-bit encoding) that support:
  - More architected vector registers.
  - Muliple mask registers.
  - Direct encoding of element width, group multiplier, rouding modes, saturation modes, tail and mask agnostic behavior, and other properties if vector instructions.

## Additional gap analysis list

- Supporting control-flow divergence (including predicated instructions with additional masking features).

- New profiles (subsets) of the scalable vector specification, particularly for embedded systems (we already have five variants of Zve).

- Data streaming architectures (e.g., adding streaming buffers for SIMD processing).

- Additional GPU-like capabiltiies for RISC-V (streaming, large regiser files, and control-flow divergence already above).

- General planning of the encoding space and instruction formats, resulting in better integration guidelines for custom instructions.

- Coprocessor interface (a broader area than just SIMD, but we want to capture the SIMD requirements).
