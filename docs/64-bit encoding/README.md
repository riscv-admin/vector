# A strawman for 64-bit vector encoding

### 32-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (5) | variant <br> (3) | vs1 <br> (5) | vs2 <br> (5) | vm <br> (1) | function <br> (6) |
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|          
| 0x57           |  $0:31$     | $0:7$            | $0:31$       | $0:31$       | $0:1$       | $0:63$              |

### 64-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd type <br> (2) | vs1 type <br> (2) | vs2 type <br> (2) | LMUL <br> (3) | vtma <br> (2) | vrnd <br> (2) |function <br> (6)                 | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|---------------|---------------|---------------|----------------------------------|-----------------|          
| 0x57           |  $0:255$    | $0:7$            | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:3$            | $0:3$             | $0:3$             | $0:7$         | $0:3$         | $0:3$         | bbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

The `type` fields in the instruction are used to encode the `sizeof` the elemental types for the destination (`vd`) and source (`vs1`, `vs2`) vector registers, according to the following table:

! `type` ($T$) | `sizeof`($T$) |
|--------------|---------------|
| 0            | 1 byte        |
| 1            | 2 bytes       |
| 2            | 4 bytes       |
| 3            | 8 bytes       |

The additional 32 bits of space in a 64-bit encoding are consumed as follows:

| 7 bits     | mandatory suffix |
| 9 bits     | 3 additional bits for each source and destination vector register, to support 256-register vector register file |
| 6 bits     | 2 additional bits for the elemental type of each source and destination vector register |
| 2 bits     | explicit mask identifier (3 bits instead of 1) |
| 1 bit      | mask polarity flag |
| 3 bits     | explicit group multiplier (LMUL) |
| 2 bits     | explicit tail and mask agnostic flags |
| 2 bits     | explicit rounding mode |
