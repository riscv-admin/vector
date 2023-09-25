# Task Group: Direct Encoding of Behavior

## Proposed charter

The RISC-V vector architecture relies on configuration registers to encode essential descriptors of instruction behavior, particularly the element width (SEW) and the register grouping (LMUL). This is a good solution for efficient encoding of vector instructions in a cramped opcode space. It also supports the creation of meta-code, which can implement different computations depending on the values of those configuration registers. These positive aspects of the RISC-V vector architecture also result in some disadvantages with respect to other architecture that more explicitly define the semantics of their vector instructions.

We realize that, in a scalable vector architecture, some configuration registers will always be necessary.
For example, the vector length cannot be directly encoded in the instruction, otherwise the code would not be *vector length agnostic*.
But there is a clear distinction between *global properties* (e.g., vector length) and *local properties* (e.g., element width).

The Direct Encoding of Behavior TG will specify a Direct Vector Extension to the RISC-V ISA.  
The Direct Vector Extension is an extension to the RISC-V ISA including vector instructions that directly encode the local properties of the vector operation in the instruction opcode.
Those instructions operate on different vector lengths and allow the writing of vector-length agnostic code. 

The resulting specification will encompass:

- A rationale and justification for pursuing the direct encoding of local propoerties of vector operations;
- A specification of any additional architectural state required by the Direct Vector Extension ISA;
- A specification of those vector instructions supported as part of this extension, including:
	- load, store, and move instructions 
		- between memory and the vector architectural state
		- between RISC-V scalar registers and the vector architectural state
	- vector-vector and scalar-vector arithmetic, compare, and logical instructions
	- vector permute instructions
	- sparse data structures compression/decompression instructions;
- Possible explicit identification of vector mask registers;
- A mapping of common code constructs with current vector ISA to new constructs with the Direct Vector Extension ISA; and
- A review of the interactions of vector load/store and prefetching of vector with the RISC-V memory models and a specification of any deviations from the standard RISC-V memory model.

## Acting leadership

- Jose Moreira (IBM)

## Proposed workplan

1. Inception (1 month) : Preliminary charter, call-for-candidates and identification of experts/resources
1. Requirements analysis (4 months)
1. Specification development (6 months)
1. Proof-of-concept and quantitative analysis (6 months)

## Proposed deliverables

### Specification deliverables
- Direct Vector Extension ISA
- Intrinsics specification for vector instructions

### Compatibility and simulation tools
- SAIL
- Hand-written ACT w/ coverage-analysis

### Proof-of-concept implementations
- GNU binutils
- GCC with intrinsics support
- QEMU
- LLVM MLIR
