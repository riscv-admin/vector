# A strawman for 64-bit vector encoding - take 4

We want to accomplish the following goals with the 64-bit encoding:
1. Expand the architected vector register space to 256 vector registers.
2. Support multiple vector mask registers. The space of vector mask registers is a subset of the space of vector registers.
3. Explicitly identify the types of each source and destination vector register, as a means to support general mixed-type instructions.
4. Explicitly identify mask agnostic and rounding-modes in each instruction.

### Do we really need 256 architected vector registers?

It is unlikely the first extension will have 256 architected vector registers, but we need to future proof the architecture.
If we think of SIMT models of execution, with mixed data types, 256 registers is not an unreasonable number.
If a vector register can store $n$ elements of size 1 byte, we would need 8 registers to hold the same $n$ elements of size 8 bytes.
The current architecture defines 32 general purpose scalar registers and 32 vector registers.
Therefore, $256 = 8 \times 32$ is not an unreasonable number.

### 32-bit vv-encoding for vector arithmetic instructions (size of field in bits)

The three vector/vector arithmetic instruction variants in the existing RISC-V "V" extension (OPIVV, OPFVV, and OPMVV) all have the same format:

| major <br> (7) | vd <br> (5) | variant <br> (3) | vs1 <br> (5) | vs2 <br> (5) | vm <br> (1) | function <br> (6) |
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|          
| 0x57           |  $0:31$     | $0:7$            | $0:31$       | $0:31$       | $0:1$       | $0:63$            |

In this strawman 64-bit encoding, we adopt different formats for each variant.
Whereas we preserve the use of major opcode 0x57 to identify vector arithmetic instructions, we take more liberty with the use of the variant and function fields.
This is justified, in part, by the approach of more explicitly encoding the type of the operands.

### 64-bit vv-encoding for HPC-oriented floating-point vector/vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd type <br> (3) | vs1 type <br> (3) | vs2 type <br> (3) | vma <br> (1) | vfprnd <br> (3) |function <br> (6)                 | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|--------------|-----------------|----------------------------------|-----------------|          
| 0x57           |  $0:255$    | 0x1              | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:7$            | $0:7$             | $0:7$             | $0:1$        | $0:7$           | bbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

### 64-bit vv-encoding for vector/vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd size <br> (2) | vs1 size <br> (2) | vs2 size <br> (2) | vma <br> (1) | vfprnd <br> (3) |function <br> (9)                 | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|--------------|-----------------|----------------------------------|-----------------|          
| 0x57           |  $0:255$    | 0x1              | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:3$            | $0:3$             | $0:3$             | $0:1$        | $0:7$           | bbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

### 64-bit vvv-encoding for three-operand vector/vector/vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd size <br> (2) | vs1 size <br> (2) | vs2 size <br> (2) | vma <br> (1) | function <br> (12)                 | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|--------------|----------------------------------|-----------------|          
| 0x57           |  $0:255$    | 0x1              | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:3$            | $0:3$             | $0:3$             | $0:1$        | bbbbbbbbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

#### Summary of encoding format changes

The additional 32 bits of space in a 64-bit encoding are consumed as follows:

| bits       | usage                                                                                                           |
|------------|-----------------------------------------------------------------------------------------------------------------|
| 7 bits     | mandatory suffix                                                                                                |
| 9 bits     | 3 additional bits for each source and destination vector register, to support 256-register vector register file |
| 9 bits     | 3 additional bits for the elemental type of each source and destination vector register                         |
| 2 bits     | explicit mask identifier (3 bits instead of 1 -- 000 reserved for no masking)                                   |
| 1 bit      | mask polarity flag                                                                                              |
| 1 bits     | explicit mask agnostic flag                                                                                     |
| 3 bits     | explicit floating-point rounding mode                                                                           |

The vector length multiplier (LMUL) and vector tail agnostic flag (vta) are not specified in every instruction and must be specified in the vtype CSR.
The expectation is that these parameters reflect a choice of the programming model and will not change during execution of a long body of code (e.g., an entire source code function).
The remaining parameters (elemental data types, mask register, mask polarity, mask agnostic, and floating-point rounding mode) are more local decisions 
and it is advantageous to both the program and the micro-architecture to have them explicitly identified in every instruction.

#### Type information

The `type` fields in the instruction are used to encode (1) the `sizeof` the elemental types for the destination (`vd`) and source (`vs1`, `vs2`) vector registers, 
and (2) additional variant information for floating-point types, according to the following table:

| `type` ($T$) | `sizeof`($T$) | floating-point variant |
|--------------|---------------|------------------------|
| 0            | 4 bytes       | IEEE fp32              |
| 1            | 8 bytes       | IEEE fp64              |
| 2            | 8 bytes       | fp32 complex           |
| 3            | 16 bytes      | fp64 complex           |
| 4            | -             | -                      |
| 5            | -             | -                      |
| 6            | -             | -                      |
| 7            | -             | -                      |

The `sizeof` for an element type of a vector register is used to compute the effective group multiplier (`EMUL` (v) = `sizeof` ($T$) $\times$ `LMUL`) for the type $T$ of that register.
This ensures that, in mixed-type instructions, all register groups (one group for vs1, one group for vs2, one group for vd) have the same number of elements.

#### Examples (`LMUL = 1`, `VLENB` = 16)

`xvfmacc.vv`<c64,f32,c32,up>\[m32/1/z\] v0, v16, v20

This instruction operates on vectors of 16 elements (`LMUL = 1`, `VLENB` = 16). The first source vector (`vs1`) consists of 16 elements of type IEEE fp32, stored in the group (v16-v19). 
The second source vector (`vs2`) consists of 16 elements of type single-precision complex, stored in the group (v20-v27).
The instruction computes the element-wise multiplication of `vs1` and `vs2`. 
This intermediate vector is then element-wise accumulated with the destination vector (`vd`), which consists of 16 elements of type double-precision complex stored in the group (v0-v15).
All arithmetic is performed in IEEE Round Up mode.
Furthermore, this instruction is executed under control of the mask in vector register 32, with positive polarity.
Only those elements of the destination vector that have a corresponding mask set to 1 in the mask register will receive the new computed value.
Other elements of the destination vector will be set to a fixed value.
