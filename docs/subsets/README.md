# Proposed standard subsets of RISC-V vector extensions

## Why

Defining standard subsets of the RISC-V vector extensions allow specific implementations to focus on a particular application scope while remaining compliant and compatible with other implementations in the same scope.
Without those standard subsets, implementors are more likely to develop their own custom subsets.
Even if those subsets follow the general guidelines of RISC-V vector extensions, they can still cause significant fragmentation of the ISA.

*Note*: [Chapter 18](https://github.com/riscv/riscv-v-spec/blob/master/v-spec.adoc#sec-vector-extensions) of the [RISC-V "V" Vector Extension](https://github.com/riscv/riscv-v-spec/blob/master/v-spec.adoc) already defines a set of standard vector extensions. 
We must consider going beyond what is already there.

## How (possible axes of subsetting)

### Data types

Floating-point support is a natural candidate for subsetting.
In the current standard, floating-point support (single and double-precision) in vectors is tied to equvalent scalar support.
Would we consider a full decoupling (vector support independent of scalar support)?
How about half-decoupling (scalar support enables but does not imply vector support)?

We can also add data types that are only supported for vectors, such as quad-precision floating-point, complex numbers, decimal floating-point.
This is more like supersetting than subsetting, so maybe it does not belong in this activity.

### Functionality

Possible functionality that can be optional:
- Masked operations
- Indexed and strided memory addressing
- Restart and/or partial execution (any failure requires full re-execution)

### Scalar vs Vector execution properties

Can we require a less strict memory order between scalar and vector instructions?
This could open the door to more efficient (performance/power/area) implementation of the vector operations.

Even more agressively, can we treat scalar and vector instructions as two independent streams?
Control-flow would remain the same, but all data dependences would apply only intra-stream.
Synchronization instructions between the two independent streams would be necessary.
This is almost like an *inline co-processor* mode.

## Candidate standard subsets

- Enterprise: Full support of all data types and functionality.
- HPC: Full support of all current data types and functionality, skip any future decimal floating-point.
- Deep learning: Floating-point and integer up to 32 bits (already there), does not require strided or indexed memory addressing.
- Lightweight deep learning: Floating-point and/or integer up to 16 bits, does not required strided or indexed memory addressing.
