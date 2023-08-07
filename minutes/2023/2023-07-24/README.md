## Meeting details

Date: 2023-07-24
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (IBM, Chair)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1y_XWJus8M5ZwSQ2cvEOzCjlOmsmXOnN4/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2023-JUN-12](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-12), [2023-JUN-26](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-26), [2023-JUL-17](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-07-17)
- Current meeting: [2023-JUL-24](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-07-24)
- Next meeting: 2023-AUG-07

## Agenda
- Approval of the Vector SIG proposed charter
- Proposed task groups
- Presentation by Guy Lemieux

## Refinement of the charter
A reminder that our draft charter is due by the end of July 2023, when it should be considered for approval by the Unprivileged Committee. The current wording is reviewed:

"
The Vector Special Interest Group (SIG) operates under the Unprivileged Committee and focuses on developing strategies, identifying gaps, and setting priorities for SIMD (Single Instruction, Multiple Data) processing capabilities within the RISC-V architecture. By SIMD processing capabilities, we mean the ability to store and manipulate collections of elements organized as vectors, matrices, tensors, and other related data structures.

The main objective of the Vector SIG is to establish RISC-V as the preferred architecture for SIMD processing across a broad range of applications, spanning from embedded systems to supercomputers. To achieve this, the Vector SIG will consistently work on enhancing the SIMD processing capabilities of the RISC-V architecture.

To enhance the SIMD processing capabilities, we will first identify gaps in the RISC-V Instruction Set Architecture and then recommend Task Groups responsible for specifying the required enhancements. These gaps will be prioritized, and a strategy will be devised to address them in the determined order of priority.

The RISC-V Vector SIG will propose a set of enhancements for SIMD processing in the RISC-V architecture. The actual specifications for these enhancements will be developed by the Task Groups formed based on the Vector SIG's recommendations. However, the final decision regarding the creation of Task Groups lies with the Technical Steering Committee.

The RISC-V Vector SIG will maintain ongoing collaboration with various groups within the RISC-V community, including Committees, SIGs, and TGs (Task Groups). Although the list of collaborators may change over time, initial collaborators will include the Vector TG (Zvfh extension), Packed SIMD TG (P extension), Graphics SIG, AI/ML SIG, Applications and Tools Committee, Vector Crypto TG, and Compiler Built-ins SIG.
"

## Refinement of the gap analysis list

Current gap analysis list:

- A self-contained behavioural specification directly encoded in the vector instructions.

- Bigger register files (e.g., to support graphics operations).

- Supporting control-flow divergence (including predicated instructions with additional masking features).

- Support for matrix processing, in two flavors:

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

- Allen Baum (Esperanto) is working on an idea for extending the vector extension with ad-hoc mask registers (rather than reusing the LSB of v0). This is in line with one of Esperanto's designs. (Allen to potentially speak on 2023-AUG-07.)

- SiFive has developed matrix processing approach that is fully integrated with vector facility (no additional registers). Jose has asked Krste Asanovic for material. 

- Philipp Tomsich asked Greg Favor if they could kick off a discussion regarding opcode space. 

## Presentation: Composable Custom eXtensions

Guy Lemieux (UBC) and Jan Gray (Gray Research) gave a presentation on their Composable Custom eXtensions proposal. This proposal has a broad impact on RISC-V and will be submitted to the proper group. Guy and Jan are looking for support from various SIGs and otther committess and we believe their proposal is relevant to us and that their work should move forward.

- Slides ([PDF](https://github.com/riscv-admin/vector/blob/main/minutes/2023/2023-07-24/CCX%20Composable%20Custom%20eXtensions%20-%20Vector%20SIG.pdf))
- Slides ([Google Docs](https://docs.google.com/presentation/d/10ky274XsgFANSlsbFhnJNPYUNYcn6EYlWNy7NtOidzI/edit#slide=id.g2316d3069ac_2_50))
- Video ([YouTube](https://www.youtube.com/watch?v=ugr3RqmWhWw))
