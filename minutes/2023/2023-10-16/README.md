## Meeting details

Date: 2023-10-16
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1NddUrkHPJukhUo8OeD7uvrWCqRaMt9zx/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2023-JUN-12](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-12), [2023-JUN-26](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-26), [2023-JUL-17](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-07-17), [2023-JUL-24](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-07-24), [2023-AUG-07](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-08-07), [2023-SEP-11](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-09-11), [2023-SEP-25](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-09-25), [2023-OCT-02](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-10-02), [2023-OCT-11](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-10-11)
- Current meeting: [2023-OCT-16](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-10-16)
- Next meeting: 2023-OCT-30

## Agenda
- Presentation from AndesTech on their work on matrix extensions: [PDF](https://github.com/riscv-admin/vector/blob/main/minutes/2023/2023-10-16/231016_V_SIG_AMM_rel.pdf), [Zoom recording](https://zoom.us/rec/share/wpfWiwdDUwOuQvMYk6-xISeFXP7R24RNxDx1_YRt-pLlXPXJ22Loc5sM4UwV9sZg.P7jho0V0eChMemK_?startTime=1697468598000)

## Refinement of the gap analysis list

Current gap analysis list:

- A self-contained behavioural specification directly encoded in the vector instructions.

- Bigger register files (e.g., to support graphics operations).

- Supporting control-flow divergence (including predicated instructions with additional masking features).

- Support for matrix processing, in three flavors:

  - Fully integrated within the vector core, reusing vector registers (like the SiFive work).

  - As an attached facility, with dedicated matrix registers (like in the Intel AMX case).

  - Hybrid of the two, such as inputs from vectors and accumulators from matrix registers (like in the IBM POWER MMA case).

- New profiles (subsets) of the scalable vector specification, particularly for embedded systems (we already have five variants of Zve).

- Data streaming architectures (e.g., adding streaming buffers for SIMD processing).

- Additional GPU-like capabiltiies for RISC-V (streaming, large regiser files, and control-flow divergence already above).

- General planning of the encoding space and instruction formats, resulting in better integration guidelines for custom instructions.

- Coprocessor interface (a broader area than just SIMD, but we want to capture the SIMD requirements).

## Prioritzed list of proposed Task Groups

1. Attached-facility variant of matrix processing.

1. Self-contained behavior directly encoded in the vector instructions.

## Ongoing work

- Allen Baum (Esperanto) is working on an idea for extending the vector extension with ad-hoc mask registers (rather than reusing the LSB of v0). This is in line with one of Esperanto's designs. (Allen was not available to speak today. We still have to schedule his presentation.)

- SiFive has developed matrix processing approach that is fully integrated with vector facility (no additional registers). Jose has asked Krste Asanovic for material. That approach is not "vector size agnostic", so it would serve as a starting point but would have to be adapted for scalable vectors.

- Philipp Tomsich asked Greg Favor if they could kick off a discussion regarding opcode space. 
