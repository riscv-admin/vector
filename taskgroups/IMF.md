# Task Group: Integrated Matrix Facility

## Proposed charter

Matrix operations are a performance critical component of deep-learning training and inference computations, scientific computing, and computational finance.
Workloads of interest include modeling and simulation of physical systems, automated trading, natural-language processing, recommendation systems, and image recognition.  
With the pervasive use of these applications in environments ranging from the datacenter to mobile applications and IoT, matrix operations for RISC-V should scale across these application domains and apply to both high-performance and resource-constrained environments.

An integrated matrix facility executes instructions that are part of the processor instruction stream and, from an architectural perspective, must follow program order. 
An integrated matrix facility is closely coupled to the vector facilities in RISC-V ISA.
An integrated matrix facility defines its own set of matrix registers, while also relying on the vector registers of the vector facility.

The Integrated Matrix Facility TG will specify an Integrated Matrix Extension to the RISC-V ISA.  
The Integrated Matrix Extension is an extension to the RISC-V ISA including scalable matrix instructions.
Those instructions operate on different operand sizes and allow the writing of matrix-geometry agnostic code. 

The resulting specification will encompass:

- An overview of the commonly used matrix operations in established algorithms and commonly used software libraries;
- A specification of the architectural state capable of holding/referencing two-dimensional matrix tiles of configurable/variable geometry;
- A specification of those matrix operations supported as part of this extension, potentially including:
	- load, store, and move operations 
		- between memory and the matrix tile architectural state
		- between RISC-V vector registers and rows/columns of the matrix tile architectural state
	- matrix-matrix, vector-matrix and scalar-matrix arithmetic operations
	- matrix permutation operations
	- sparse-matrix compression/decompression;
- A predication mechanism to control operations performed on matrix tiles;
- A mapping of common matrix operations onto the newly defined instructions in the Integrated Matrix Extension; and
- A review of the interactions of matrix load/store and prefetching of matrices with the RISC-V memory models and a specification of any deviations from the standard RISC-V memory model.

## Acting leadership

- Jose Moreira (IBM)

## Proposed workplan

1. Inception (1 month) : Preliminary charter, call-for-candidates and identification of experts/resources
1. Requirements analysis (4 months)
1. Specification development (6 months)
1. Proof-of-concept and quantitative analysis (6 months)

## Proposed deliverables

### Specification deliverables
- Integrated Matrix Extension ISA
- Intrinsics specification for matrix instruction

### Compatibility and simulation tools
- SAIL
- Hand-written ACT w/ coverage-analysis

### Proof-of-concept implementations
- Linux kernel (e.g., context switching for matrix tiles)
- oneDNN (https://github.com/oneapi-src/oneDNN)
- GNU binutils
- GCC with intrinsics support
- QEMU
- LLVM MLIR
