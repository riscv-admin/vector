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



The RISC-V Vector SIG will deliver a series of recommended enhancement areas. for SIMD processing in the RISC-V architecture - the actual specification of the enhancements will be the result of work by the Task Groups spawned by recommendation of the RISC-V Vector SIG. (Vector SIG recommends and specifies the work of the task groups - final decision on Technical Group creation is by the Technical Steering Committee.)



RISC-V Vector SIG will continuously interact with other groups, including Committees, SIGs, and TGs within the RISC-V community. Although we expect our list of collaborators to be dynamic we can identify some initial collaborators: Vector TG (Zvfh extension), Packed SIMD TG (P extension), Graphics SIG, AI/ML SIG, Applications and Tools Committee, Vector Crypto TG, Compiler Built-ins SIG.
"


## Refinement of the gap analysis list



We go again through the gap analysis list:



- A self-contained behavioural specification for vector instructions.



- Supporting control flow divergence



- Support for matrix multiply in two flavours:

* Integrated within the vector core, reusing vector registers

* As an attached facility, with dedicated matrix registers (like in the Intel AMX case)



- New profiles (subsets) of the vector spec. Jose would like to collect any specific requirements about new variants of Zve (vector for the embedded domain). We are aware that there are already 5 variants of Zve (Ken Dockser brings this up).



- Predicated instructions. This is removed from the list because there seem to be agreement that predicated instructions are just one particular approximation to control flow divergence, which is already present in the list. Mask registers are already providing predication and there is a preference on building on top of masking.



- Streaming of data (Luca Benini's work from ETH Zurich is mentioned again).



- General planning of the encoding space and instruction formats.



Allen Baum (Esperanto) tells us about an idea he is working on for extending the vector extension with ad-hoc mask registers (rather than reusing the LSB of v0). This is in line with one of Esperanto's designs.



The reason why v0 was chosen to be a special register is asked by Jose. Ken Dockser mentions instruction encoding space being very tight. Seems like Allen's proposal may benefit from 64 bits instruction.



Jose thinks that the subject of coprocessors likely goes beyond the vector scope, which is a view also expressed in the previous session by Mark Himelsteain.



As a response to that argument, at least two members (Guy and Abel) highlight that the subject of coprocessors entails two aspects:



- Reserving ISA ranges and recommending instruction formats for common custom vector extensions. A good example is the .insn statement supported on gcc, that allows certain instructions to be easily tried out without even modifying the compiler.



- A communication bus, which can be regarded as a non-ISA subject (and therefore as something that gets a different priority as a subject to be discussed by the group).



Guy Lemiux accepts Jose's invitation to talk about work on coprocessors done within his university research group, both in terms of ISA implications and communication buses. This will be scheduled whenever Guy is ready.



An additional point from the graphics domain is added to the list of topics for the gap analysis: a bigger register file, with more than 32 registers. That feature will also demand 64 bits instruction encoding (a recurrent subject).



We know that the vector register file has no limitation preventing implementations to scale up in width, with VLEN being implementation-dependent. Having wide registers is actually good for shading many pixels in one go.



However having just 32 registers seems like a bottleneck when compared with typical GPUs, having no less than 100 registers. If a GPU based on RISC-V is limited to 32 registers, complex shaders will get register spilling to the stack frame.
