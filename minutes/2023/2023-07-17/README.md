## Meeting details

Date: 2023-07-17
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (IBM, Chair)
- Abel Bernabeu (Vice-chair, Esperanto)
- Qiu Jing (T-Head)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1y_XWJus8M5ZwSQ2cvEOzCjlOmsmXOnN4/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2023-JUN-12](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-12), [2023-JUN-26](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-06-26)
- Current meeting: [2023-JUL-17](https://github.com/riscv-admin/vector/tree/main/minutes/2023/2023-07-17) (rescheduled for meeting on 2023-JUL-10)
- Next meeting: 2023-JUL-24 (back to normal schedule)

## Agenda
- Refinement of the charter
- Refinement of the gap analysis list
- Overview of matrix processing work (attached facilty variant)

## Refinement of the charter
A reminder that our draft charter is due by the end of July 2023, when it should be considered for approval by the Unprivileged Committee. The current wording is reviewed:

"
The Vector SIG is managed under the Unprivileged Committee, and is intended to develop the strategy, gaps, and prioritizations for all SIMD processing capabilities within RISC-V. We define SIMD processing capabilities to include the storage and manipulation of collections of elements organized as vectors, matrices, tensors, and other data structures that are related to vectors.

The goal of Vector SIG is to make RISC-V the architecture of choice for SIMD processing in a wide spectrum of applications, from embedded systems to supercomputers. RISC-V Vector SIG will continuously pursue enhancements to the SIMD processing capabilities of RISC-V architecture to achieve that goal.

We will achieve enhancements to RISC-V SIMD processing capabilities by identifying gaps in coverage of the RISC-V Instruction Set Architecture and recommending Task Groups that will develop the specification of those enhancements. As we identify the gaps, we will always prioritize the list of gaps and develop a strategy to fill those gaps in the adopted priority order.

The RISC-V Vector SIG will deliver a series of recommended enhancement areas for SIMD processing in the RISC-V architecture - the actual specification of the enhancements will be the result of work by the Task Groups spawned by recommendation of the RISC-V Vector SIG. (Vector SIG recommends and specifies the work of the Task Groups - final decision on Task Group creation is by the Technical Steering Committee.)

RISC-V Vector SIG will continuously interact with other groups, including Committees, SIGs, and TGs within the RISC-V community. Although we expect our list of collaborators to be dynamic we can identify some initial collaborators: Vector TG (Zvfh extension), Packed SIMD TG (P extension), Graphics SIG, AI/ML SIG, Applications and Tools Committee, Vector Crypto TG, Compiler Built-ins SIG.
"

## Refinement of the gap analysis list

Current gap analysis list:

- A self-contained behavioural specification directly encoded in the vector instructions.

- Bigger register files (e.g., to support graphics operations).

- Supporting control-flow divergence (including predicated instructions with additional masking features).

- Support for matrix processing, in two flavours:

  - Integrated within the vector core, reusing vector registers (like in the IBM POWER MMA case).

  - As an attached facility, with dedicated matrix registers (like in the Intel AMX case).

- New profiles (subsets) of the scalable vector specification, particularly for embedded systems (we already have five variants of Zve).

- Data streaming architectures (e.g., adding streaming buffers for SIMD processing).

- Additional GPU-like capabiltiies for RISC-V (streaming, large regiser files, and contro-flow divergence already above).

- General planning of the encoding space and instruction formats, resulting in better integration guidelines for custom instructions.

- Coprocessor interface (a broader area than just SIMD, but we want to capture the SIMD requirements).

## Ongoing work

- Allen Baum (Esperanto) tells us about an idea he is working on for extending the vector extension with ad-hoc mask registers (rather than reusing the LSB of v0). This is in line with one of Esperanto's designs. (Allen to potentially speak on 2023-JUL-24.)

- Guy Lemiux to talk about work on coprocessors done within his university research group, both in terms of ISA implications and communication buses. (To be scheduled.)

## Matrix processing (attached facility variant)
