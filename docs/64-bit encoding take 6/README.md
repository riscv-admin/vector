# A strawman for 64-bit vector encoding - take 5

We want to accomplish the following goals with the 64-bit encoding:
1. Expand the architected vector register space to 256 vector registers.
2. Support multiple vector mask registers. The space of vector mask registers is a subset of the space of vector registers.
3. Explicitly identify the element-width of each source and destination vector register, as a means to support general mixed-type instructions.
4. Explicitly identify mask agnostic and rounding-modes in each instruction.
5. Support a programming model with all vectors having the same number of elements.

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

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd size <br> (2) | vs1 size <br> (2) | vs2 size <br> (2) | vma <br> (1) | vfprnd (3) | function <br> (9)                   | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|--------------|------------|-------------------------------------|-----------------|          
| 0x57           |  $0:255$    | 0x1              | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:3$            | $0:3$             | $0:3$             | $0:1$        | $0:7$      | bbbbbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

#### Summary of encoding format changes

The additional 32 bits of space in a 64-bit encoding are consumed as follows:

| bits       | usage                                                                                                           |
|------------|-----------------------------------------------------------------------------------------------------------------|
| 7 bits     | mandatory suffix                                                                                                |
| 9 bits     | 3 additional bits for each source and destination vector register, to support 256-register vector register file |
| 6 bits     | 2 additional bits for the elemental type of each source and destination vector register                         |
| 2 bits     | explicit mask identifier (3 bits instead of 1 -- 000 reserved for no masking)                                   |
| 1 bit      | mask polarity flag                                                                                              |
| 1 bits     | explicit mask agnostic flag                                                                                     |
| 3 bits     | explicit floating-point rounding mode                                                                           |
| 3 bits     | 3 additional bits for the function code, expanding the enconding space by 7x                                    |

The vector length multiplier (LMUL) and vector tail agnostic flag (vta) are not specified in every instruction and must be specified in the vtype CSR.
The expectation is that these parameters reflect a choice of the programming model and will not change during execution of a long body of code (e.g., an entire source code function).
The remaining parameters (elemental data sizes, mask register, mask polarity, mask agnostic, and floating-point rounding mode) are more local decisions 
and it is advantageous to both the program and the micro-architecture to have them explicitly identified in every instruction.

#### Element size information

The `size` fields in the instruction are used to encode the `sizeof` the elemental types for the destination (`vd`) and source (`vs1`, `vs2`) vector registers.
The `size` field, combined with the `function` field defines the type of the operand.
For complex-valued operands, the `size` refers to the size of each real/imaginary field.
Sizes are encoded according to the following table:

| `size` field | size of element | floating-point variant                          |
|--------------|-----------------|-------------------------------------------------|
| 0            | 2 bytes         | IEEE half-precision or bfloat16 real or complex |
| 1            | 4 bytes         | IEEE single-precision real or complex           |
| 2            | 8 bytes         | IEEE double-precision real or complex           |
| 3            | 16 bytes        | IEEE quad-precision real or complex             |

The size for an element type of a vector operand is used to compute the effective group multiplier for the registers `v` containing that operand.
For real-valued operands, `EMUL` (v) = `size`(v) $\times$ `LMUL`
This ensures that, in mixed-type instructions, all register groups (one group for vs1, one group for vs2, one group for vd) have the same number of elements.
The number of elements in a group is always `VLENB` $\times$ `LMUL`

#### Examples (`LMUL = 1`, `VLENB` = 16)

`xvrcmacc.vv`<`vd size`=double, `vs1 size`=single, `vs2 size`=single, `vm`=32, `vfprnd`=up, `polarity`=positive, `agnostic`=yes> v0, v16, v20

The instruction computes vd[i] += vs1[i] * vs2[i], with vs1 storing real values and vs2 and vd storing complex values. (These semantics are defined by the function code corresponding to `xvrcmacc.vv`.)
This instruction operates on vectors of 16 elements (`LMUL = 1`, `VLENB` = 16). The first source vector (`vs1`) consists of 16 elements of type IEEE fp32, stored in the group (v16-v19). 
The second source vector (`vs2`) consists of 16 elements of type single-precision complex, stored in the group (v20-v27).
The instruction computes the element-wise multiplication of `vs1` and `vs2`. 
This intermediate vector is then element-wise accumulated with the destination vector (`vd`), which consists of 16 elements of type double-precision complex stored in the group (v0-v15).
All arithmetic is performed in IEEE Round Up mode.
Furthermore, this instruction is executed under control of the mask in vector register 32, with positive polarity.
Only those elements of the destination vector that have a corresponding mask set to 1 in the mask register will receive the new computed value.
Other elements of the destination vector will be set to a fixed value.

#### List of HPC-oriented floating-point vector/vector arithmetic instructions

| instruction    | `vs1`   | `vs2`   | `vd`    | semantics                          |
|----------------|---------|---------|---------|------------------------------------|
| `xvrradd.vv`   | real    | real    | real    | vd[i] = vs1[i] + vs2[i]            |
| `xvccadd.vv`   | complex | complex | complex | vd[i] = vs1[i] + vs2[i]            |
| `xvrcadd.vv`   | real    | complex | complex | vd[i] = vs1[i] + vs2[i]            |
| `xvrrsub.vv`   | real    | real    | real    | vd[i] = vs1[i] - vs2[i]            |
| `xvccsub.vv`   | complex | complex | complex | vd[i] = vs1[i] - vs2[i]            |
| `xvrcsub.vv`   | real    | complex | complex | vd[i] = vs1[i] - vs2[i]            |
| `xvcrsub.vv`   | complex | real    | complex | vd[i] = vs1[i] - vs2[i]            |
| `xvrrmul.vv`   | real    | real    | real    | vd[i] = vs1[i] * vs2[i]            |
| `xvccmul.vv`   | complex | complex | complex | vd[i] = vs1[i] * vs2[i]            |
| `xvrcmul.vv`   | real    | complex | complex | vd[i] = vs1[i] * vs2[i]            |
| `xvrrdiv.vv`   | real    | real    | real    | vd[i] = vs1[i] / vs2[i]            |
| `xvccdiv.vv`   | complex | complex | complex | vd[i] = vs1[i] / vs2[i]            |
| `xvrcdiv.vv`   | real    | complex | complex | vd[i] = vs1[i] / vs2[i]            |
| `xvcrdiv.vv`   | complex | real    | complex | vd[i] = vs1[i] / vs2[i]            |
|----------------|---------|---------|---------|------------------------------------|
| `xvrrmacc.vv`  | real    | real    | real    | vd[i] = +(vs1[i] * vs2[i]) + vd[i] |
| `xvccmacc.vv`  | complex | complex | complex | vd[i] = +(vs1[i] * vs2[i]) + vd[i] |
| `xvrcmacc.vv`  | real    | complex | complex | vd[i] = +(vs1[i] * vs2[i]) + vd[i] |
| `xvrrnmacc.vv` | real    | real    | real    | vd[i] = -(vs1[i] * vs2[i]) - vd[i] |
| `xvccnmacc.vv` | complex | complex | complex | vd[i] = -(vs1[i] * vs2[i]) - vd[i] |
| `xvrcnmacc.vv` | real    | complex | complex | vd[i] = -(vs1[i] * vs2[i]) - vd[i] |
| `xvrrmsac.vv`  | real    | real    | real    | vd[i] = +(vs1[i] * vs2[i]) - vd[i] |
| `xvccmsac.vv`  | complex | complex | complex | vd[i] = +(vs1[i] * vs2[i]) - vd[i] |
| `xvrcmsac.vv`  | real    | complex | complex | vd[i] = +(vs1[i] * vs2[i]) - vd[i] |
| `xvrrnmsac.vv` | real    | real    | real    | vd[i] = -(vs1[i] * vs2[i]) + vd[i] |
| `xvccnmsac.vv` | complex | complex | complex | vd[i] = -(vs1[i] * vs2[i]) + vd[i] |
| `xvrcnmsac.vv` | real    | complex | complex | vd[i] = -(vs1[i] * vs2[i]) + vd[i] |
| `xvrrmadd.vv`  | real    | real    | real    | vd[i] = +(vs1[i] * vd[i]) + vs2[i] |
| `xvccmadd.vv`  | complex | complex | complex | vd[i] = +(vs1[i] * vd[i]) + vs2[i] |
| `xvrcmadd.vv`  | real    | complex | complex | vd[i] = +(vs1[i] * vd[i]) + vs2[i] |
| `xvrrnmadd.vv` | real    | real    | real    | vd[i] = -(vs1[i] * vd[i]) - vs2[i] |
| `xvccnmadd.vv` | complex | complex | complex | vd[i] = -(vs1[i] * vd[i]) - vs2[i] |
| `xvrcnmadd.vv` | real    | complex | complex | vd[i] = -(vs1[i] * vd[i]) - vs2[i] |
| `xvrrmsub.vv`  | real    | real    | real    | vd[i] = +(vs1[i] * vd[i]) - vs2[i] |
| `xvccmsub.vv`  | complex | complex | complex | vd[i] = +(vs1[i] * vd[i]) - vs2[i] |
| `xvrcmsub.vv`  | real    | complex | complex | vd[i] = +(vs1[i] * vd[i]) - vs2[i] |
| `xvrrnmsub.vv` | real    | real    | real    | vd[i] = -(vs1[i] * vd[i]) + vs2[i] |
| `xvccnmsub.vv` | complex | complex | complex | vd[i] = -(vs1[i] * vd[i]) + vs2[i] |
| `xvrcnmsub.vv` | real    | complex | complex | vd[i] = -(vs1[i] * vd[i]) + vs2[i] |
|----------------|---------|---------|---------|------------------------------------|
| `xvrrmin.vv`   | real    | real    | real    | vd[i] = min(vs1[i],vs2[i])         |
| `xvrrmax.vv`   | real    | real    | real    | vd[i] = max(vs1[i],vs2[i])         |
|----------------|---------|---------|---------|------------------------------------|
| `xvrrsgnj.vv`  | real    | real    | real    | vd[i] = sgn(vs1[i])*abs(vs2[i])    |
| `xvrrsgnjn.vv` | real    | real    | real    | vd[i] = -sgn(vs1[i])*abs(vs2[i])   |
| `xvrrsgnjx.vv` | real    | real    | real    | vd[i] = sgn(vs1[i])*vs2[i]         |
|----------------|---------|---------|---------|------------------------------------|
| `xvrreq.vv`    | real    | real    | real    | vd[i] = vs1[i] == vs2[i]           |
| `xvcceq.vv`    | complex | complex | complex | vd[i] = vs1[i] == vs2[i]           |
| `xvrrne.vv`    | real    | real    | real    | vd[i] = vs1[i] != vs2[i]           |
| `xvccne.vv`    | complex | complex | complex | vd[i] = vs1[i] != vs2[i]           |
| `xvrrlt.vv`    | real    | real    | real    | vd[i] = vs1[i] < vs2[i]            |
| `xvrrle.vv`    | real    | real    | real    | vd[i] = vs1[i] <= vs2[i]           |
| `xvrrgt.vv`    | real    | real    | real    | vd[i] = vs1[i] > vs2[i]            |
| `xvrrge.vv`    | real    | real    | real    | vd[i] = vs1[i] >= vs2[i]           |
