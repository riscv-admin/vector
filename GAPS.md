# Vector SIG Gap Analysis

This is a living document maintained by the RISC-V Vector SIG in fulfillment of our [charter](https://github.com/riscv-admin/vector/blob/main/CHARTER.md). 
It reflects our assessment of the current capabilities of RISC-V SIMD processing and our vision for enhancing those capabilities. 
The topics in this gap analysis are discussed in the Vector SIG technical meetings, as listed in the [RISC-V Technical Meetings Calendar](https://calendar.google.com/calendar/u/0/embed?src=tech.meetings@riscv.org). 
A topic is moved to this document when there is consensus that it should be pursued and enough clarity on what to pursue. 
For each topic, we will propose a Task Group to pursue the work in developing the specification of the necessary enhancements.
An initial Task Group will be formed to perform the preliminary work and prepare a true *Task Group proposal* that can be brought in front of the Technical Steering Committee for approval.  

## Common Guidelines

Each task group is encouraged to explore as many alternatives it wants while developing its proposed enhancement, with proper respect to the schedule that was committed and approved.
There are some general guidelines that we recommend all task groups spawned from the Vector SIG to follow.
These include guidelines regarding instruction encoding, as detailed below.

### Instruction Encoding

Most, if not all, enhancements to be prepared by our spawned Task Groups will require new instructions with their own encoding.
The encoding space for the traditional 32-bit RISC-V instructions is already cramped and our proposed enhancements are likely to exacerbate that problem.
There is ongoing activity to address the problem of limited encoding space.
Possible solutions include (1) focusing on 64-bit encoding, (2) dynamic encoding, with the meaning of encoding dependent on context, and (3) using only the custom encoding space.
Each of these solutions has its own advantages and disadvantages, and we are likely to depend on the work of other committees before a *preferred solution* emerges.
Even if and when a preferred solution emerges, that does not necessarily mean that the preferred solution should be adopted by every proposed RISC-V SIMD enhancement.

For now, we recommend the following course of action for the various task groups working on SIMD enhancements:
1. Focus on functionality first. That is, define the instructions and their semantics, making clear what the input and output registers are. Specify the sizes of the register sets. Keep a count of how many instructions and instruction forms will have to be encoded. Do not worry, at first, about specific encodings for the instructions.
2. There is no harm (or maybe *not much harm*) in specifying 64-bit encodings for the instructions. Treat those specifications as *exploratory*. That is, we are investigating how things would look like if the instructions were encoded in 64 bits. 64-bit encodings are likely to become more popular with time, and we may need some general guidelines (from other committees) on what 64-bit encodings should look like. Any 64-bit encoding that we first define is more likely to serve as input for those other committees than to become a final form of a 64-bit instruction.
