## Meeting details

Date: 2024-05-13
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw)
- [Video](https://drive.google.com/file/d/1NddUrkHPJukhUo8OeD7uvrWCqRaMt9zx/view)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2024-JAN-08](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-08), [2024-JAN-22](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-22), [2024-FEB-05](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-05), [2024-FEB-19](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-19), [2024-MAR-04](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-03-04), [2024-MAR-18](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-03-18), [2024-APR-01](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-01), [2024-APR-15](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-15), [2024-APR-29](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-29)
- Current meeting: [2024-MAY-13](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-05-13)
- Next meeting: 2024-JUN-10 (May 27th is Memorial Day in the United States)

## Agenda
- [Zoom recording](https://zoom.us/rec/share/o2yTPvgZZRAIbQr_p8OZgp8V1R5wXfI5Yxo27nrS50IXnBql6M70eDLkvlAgWfSA.MhtvGgD_SVnGsLER?startTime=1715612556000)
- Jose's presentation on emulating SIMT (GPU) behavior using vector architectures [PDF](SIMT_through_SIMD.pdf).
- Backup topic: Continue discussion on subsetting of the existing RISC-V V extensions to specs that can be implemented by different classes of RISC-V processors.

### Subsetting of existing RISC-V V extensions
- Does RISC-V publish a *process* for subsetting and then vendors follow that process to produce a *legal subset*?
- Does RISC-V publish a list of *legal subsets*, presumably derived by following the process mentioned above?

### Jose's wishlist for self-contained vector instructions
- Explicit type identifier (subsumes but goes beyond SEW, like floating-point vs fixed-point). (6 bits)
- Explicit LMUL value. (3 bits)
- Vector mask register specifier. (5 bits)
- Vector tail agnostic and mask agnostic flags. (2 bits)
- Vector mask register polarity flag. (1 bit)
- Vector rounding mode register (fixed- and floating-point). (2 bits)
- Larger vector register file. (64/128/256 registers?) (4/8/12 additional bits)

### Other wishlist items from Vector SIG members
- Ability to encode large numbers of vector registers (256+) - Abel (will present reasons for large register files on 04/29)
- Separate vector mask registers - Ken (Allen will present an approach to encoding more mask registers/separate mask registers)
- More detailed type specification (e.g., 5 bits per register?) - (This issue can be better addressed by Roger and/or Krste)
- More bits for rounding mode (e.g., 3 bits) - Nicolas
- More general metadata for vector register data - Guy

### A strawman for 64-bit vector encoding

#### 32-bit vv-encoding for vector arithmetic instructions

| major (7 bits) | vd (5 bits) | variant (3 bits) | vs1 (5 bits) | vs2 (5 bits) | vm (1 bit) | function (6 bits) |
|----------------|-------------|------------------|--------------|--------------|------------|-------------------|          
| 0x57           |  0-31       | 0-7              | 0-31         | 0-31         | 0-1        | 0-63              |

#### 64-bit vv-encoding for vector arithmetic instructions

| suffix (7 bits) | major (5 bits) | vd (7 bits) | variant (3 bits) | vs1 (7 bits) | vs2 (7 bits) | vm (7 bits) | function (6 bits) | mask? (1 bit) | polarity (1 bit) | type (6 bits) | LMUL (3 bits) | vtma (2 bits) | vrnd (2 bits) |
|-----------------|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|---------------|------------------|---------------|---------------|---------------|---------------|          
| 0111111         | bbbbb          |  0-127      | 0-7              | 0-127        | 0-127        | 0-127       | 0-63            | 0-1           | 0-1              | 0-63          | 0-7           | 0-3           | 0-3           |

| suffix (7 bits) | major (5 bits) | vd (6 bits) | variant (3 bits) | vs1 (6 bits) | vs2 (6 bits) | vm (6 bits) | function (7 bits) | mask? (1 bit) | polarity (1 bit) | type (9 bits) | LMUL (3 bits) | vtma (2 bits) | vrnd (2 bits) |
|-----------------|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|---------------|------------------|---------------|---------------|---------------|---------------|          
| 0111111         | bbbbb          |  0-63       | 0-7              | 0-63         | 0-63         | 0-63        | 0-127             | 0-1           | 0-1              | 3 x 0-7       | 0-7           | 0-3           | 0-3           |

## Integrated Matrix Extensions (IME) Task Group resources
- [Groups.io](https://lists.riscv.org/g/tech-integrated-matrix-extension)
- [Github](https://github.com/riscv-admin/integrated-matrix-extension)
- [Zoom](https://zoom.us/j/93397157767?pwd=UE0vbWJEU0dFSXR4dlp5NGZjaUJJdz09) Meeting ID: 933 9715 7767, Passcode: 051351
- Guido Araujo is the acting chair for the IME TG.
- Jose Moreira is the acting vice-chair for the IME TG.

## SiFive matrix extensions
The following SiFive matrix extensions are documented in their [website](https://www.sifive.com/documentation), under "SiFive Intelligence Extensions":
- [SiFive Int8 Matrix Multiplication Extensions Specification](https://sifive.cdn.prismic.io/sifive/60d5a660-3af0-49a3-a904-d2bbb1a21517_int8-matmul-spec.pdf)
- [Matrix Multiply Accumulate Instruction (Xsfvfwmaccqqq) Extension Specification](https://sifive.cdn.prismic.io/sifive/c391d53e-ffcf-4091-82f6-c37bf3e883ed_xsfvfwmaccqqq-spec.pdf)
These SiFive matrix extensions fall in our "Option C: Multiple matrices in one vector register." To be more precise, multiple *matrix tiles* can fit in a single vector register.

## Next work items for Vector SIG
- We expect many of the members in RISC-V Vector SIG to participate in the IME and AME TGs.
- We will organize regular updates from the IME TG, to be presented at the regular Vector SIG meetings.
- Continue to investigate and explore sparsity support for matrix computations with RISC-V. Goals are (1) to provide a sanity check for the active matrix extension activities, so that they do not preclude future extensions with sparsity support, and (2) feed into future vector extensions activities that will spec sparsity support.
- Self-contained vector instructions (likely with 64-bit encoding) that support:
  - More architected vector registers.
  - Muliple mask registers.
  - Direct encoding of element width, group multiplier, rouding modes, saturation modes, tail and mask agnostic behavior, and other properties if vector instructions.

## Additional gap analysis list

- Supporting control-flow divergence (including predicated instructions with additional masking features).

- New profiles (subsets) of the scalable vector specification, particularly for embedded systems (we already have five variants of Zve).

- Data streaming architectures (e.g., adding streaming buffers for SIMD processing).

- Additional GPU-like capabiltiies for RISC-V (streaming, large regiser files, and control-flow divergence already above).

- General planning of the encoding space and instruction formats, resulting in better integration guidelines for custom instructions.

- Coprocessor interface (a broader area than just SIMD, but we want to capture the SIMD requirements).
