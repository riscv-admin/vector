## Meeting details

Date: 2024-01-08
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1NddUrkHPJukhUo8OeD7uvrWCqRaMt9zx/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: 
- Current meeting: [2024-JAN-08](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-08)
- Next meeting: 2024-JAN-22

## Agenda
- [Zoom recording]()
- Transition of matrix extension work to Integrated Matrix Extensions (IME) Task Group.
- SiFive matrix extensions.
- Next work items for Vector SIG.

## Integrated Matrix Extensions (IME) Task Group resources:
- [Groups.io](https://lists.riscv.org/g/tech-integrated-matrix-extension)
- [Charter](https://github.com/riscv-admin/integrated-matrix-extension)
- [Zoom](https://zoom.us/j/93397157767?pwd=UE0vbWJEU0dFSXR4dlp5NGZjaUJJdz09) Meeting ID: 933 9715 7767, Passcode: 051351

## SiFive matrix extensions
The following SiFive matrix extensions are documented in their [website](https://www.sifive.com/documentation), under "SiFive Intelligence Extensions":
- [SiFive Int8 Matrix Multiplication Extensions Specification](https://sifive.cdn.prismic.io/sifive/60d5a660-3af0-49a3-a904-d2bbb1a21517_int8-matmul-spec.pdf)
- [Matrix Multiply Accumulate Instruction (Xsfvfwmaccqqq) Extension Specification](https://sifive.cdn.prismic.io/sifive/c391d53e-ffcf-4091-82f6-c37bf3e883ed_xsfvfwmaccqqq-spec.pdf)
These SiFive matrix extensions fall in our "Option C: Multiple matrices in one vector register." To be more precise, multiple *matrix tiles* can fit in a single vector register.

