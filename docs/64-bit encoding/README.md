# A strawman for 64-bit vector encoding

### 32-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (5) | variant <br> (3) | vs1 <br> (5) | vs2 <br> (5) | vm <br> (1) | function <br> (6) |
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|          
| 0x57           |  $0:31$     | $0:7$            | $0:31$       | $0:31$       | $0:1$       | $0:63$              |

### 64-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd type <br> (2) | vs1 type <br> (2) | vs2 type <br> (2) | LMUL <br> (3) | vtma <br> (2) | vrnd <br> (2) |function <br> (6)                 | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|---------------|---------------|---------------|----------------------------------|-----------------|          
| 0x57           |  $0:255$    | $0:7$            | $0:255$      | $0:255$      | $0:7$       | $0:1$             | $0:3$            | $0:3$             | $0:3$             | $0:7$         | $0:3$         | $0:3$         | bbbnnn <br> ${\sf nnn} \neq 111$ | 1111111         |

### Summary of encoding format changes

The additional 32 bits of space in a 64-bit encoding are consumed as follows:

| bits       | usage                                                                                                           |
|------------|-----------------------------------------------------------------------------------------------------------------|
| 7 bits     | mandatory suffix                                                                                                |
| 9 bits     | 3 additional bits for each source and destination vector register, to support 256-register vector register file |
| 6 bits     | 2 additional bits for the elemental type of each source and destination vector register                         |
| 2 bits     | explicit mask identifier (3 bits instead of 1)                                                                  |
| 1 bit      | mask polarity flag                                                                                              |
| 3 bits     | explicit group multiplier (LMUL)                                                                                |
| 2 bits     | explicit tail and mask agnostic flags                                                                           |
| 2 bits     | explicit rounding mode                                                                                          |

### Tyoe information

The `type` fields in the instruction are used to encode the `sizeof` the elemental types for the destination (`vd`) and source (`vs1`, `vs2`) vector registers, according to the following table:

| `type` ($T$) | `sizeof`($T$) |
|--------------|---------------|
| 0            | 1 byte        |
| 1            | 2 bytes       |
| 2            | 4 bytes       |
| 3            | 8 bytes       |

The `sizeof` for an element type of a vector register is used to compute the effective group multiplier (${\sf EMUL}({\sf v}) = {\sf sizeof}({\sf v}) \times {\sf LMUL}$) for that register.
This ensures that, in mixed-type instructions, all registers have the same number of elements.

### Do we really need 256 architected vector registers?

It is unlikely the first extension will have 256 architected vector registers, but we need to future proof the architecture.
If we think of SIMT models of execution, with mixed data types, 256 registers is not an unreasonable number.
If a vector register can store $n$ elements of size 1 byte, we would need 8 registers to hold the same $n$ elements of size 8 bytes.
The current architecture defines 32 general purpose scalar registers and 32 vector registers.
Therefore, $256 = 8 \times 32$ is not an unreasonable number.

### A simple example: BLAS daxpy

The BLAS `daxpy` routines computes $y \leftarrow \alpha x + y$. 
The scalar $\alpha$ and vectors $x$ and $y$ are of type double-precision (${\sf fp64}$).
A simplified signature is

<code>
void daxpy(int n, double alpha, double *x, double *y);
</code>

Using existing RISC-V vector instructions, the routine can be coded as follows:

<code>
# Let a0 = n (number of elements)
# Let fa0 = alpha (scalar multiplier)
# Let a1 = address of x vector
# Let a2 = address of y vector

# Register setup
vsetvli t0, zero, e64, m1        # Set the vector length for 64-bit elements
vl  t1, vlenb(t0)                # Load the vector length in bytes to t1

loop:
    beqz a0, end                 # If n == 0, exit the loop

    vsetvli t0, a0, e64, m1      # Set the vector length for the remaining elements

    vle64.v v1, (a1)             # Load vector x
    vle64.v v2, (a2)             # Load vector y

    vfmacc.vf v2, fa0, v1        # v2 = fa0 * v1 + v2

    vse64.v v2, (a2)             # Store result back to y

    # Update pointers and counter
    add a1, a1, t1               # Move x pointer
    add a2, a2, t1               # Move y pointer
    sub a0, a0, t0               # Decrement element count by the vector length

    j loop                       # Repeat the loop

end:
    # Exit point
    ret
</code>
