## Meeting details

Date: 2024-12-09
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw/edit?pli=1#slide=id.p1)
- [Video](https://wiki.riscv.org/display/HOME/Meeting+Disclosures)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings: [2024-JAN-08](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-08), [2024-JAN-22](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-01-22), [2024-FEB-05](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-05), [2024-FEB-19](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-02-19), [2024-MAR-04](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-03-04), [2024-MAR-18](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-03-18), [2024-APR-01](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-01), [2024-APR-15](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-15), [2024-APR-29](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-04-29), [2024-MAY-13](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-05-13), [2024-JUN-10](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-06-10), [2024-JUL-08](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-07-08), [2024-JUL-22](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-07-22), [2024-AUG-05](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-08-05), [2024-AUG-19](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-08-19), [2024-SEP-16](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-09-16), [2024-SEP-30](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-09-30), [2024-OCT-28](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-10-28), [2024-NOV-11](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-11-11), [2024-NOV-25](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-11-25)
- Current meeting: [2024-DEC-09](https://github.com/riscv-admin/vector/tree/main/minutes/2024/2024-12-09)
- Next meeting: 2025-JAN-06

## Agenda
- [Zoom recording](https://zoom.us/rec/share/cT8tEJ8n56OTojSBP3sa0W-sAYMP9Yi1c54wYuep6UYJRqdWdZgDAHESNcuJyylZ.PH7qJuvpc7KEjA1q?startTime=1733760245000)
- [AI-generated summary](https://github.com/riscv-admin/vector/blob/main/minutes/2024/2024-12-09/AI%20Meeting%20Summary%20for%20Vector%20SIG%20Meeting%20-%202024-DEC-09.pdf) - Use with caution! I read it, and it is not bad but there is some confusion. I will do some cleanup and post an edited version.

### Next steps
1. We will pursue (separate) fast-track routes to standardize the three most important items for video processing support:
    1. The dot-product instructions are already under a fast-track process. We should participate in that process.
    2. The zip/unzip instructions are well understood and there is even an [initial proposal](https://github.com/riscv-admin/vector/blob/main/minutes/2024/2024-12-09/Vzip%20Fast%20Track%20Architecture%20Proposal.pdf). (Punit Agrawal will take the lead in drafting a chart for that work.)
    3. Absolute differences instructions. Punit Agrawal will also take the lead on this one.
2. We will start support for FP8 data types with conversion-only instructions. Probably these will be convertion to/from 16-bit floating-point types from/to 8-bit floating-point types. We will focus on the more popular ML formats (E5M2 and E4M3), and not worry about block formats (e.g., MX) yet. (Krste Asanović will ask Andrew Waterman to prepare a strawman proposal.)

### Prioritize candidate work topics
1. Subsetting of the existing RISC-V "V" vector extension for specific types of cores (e.g., IoT, embedded, AI/ML, HPC).
2. Self-contained vector instructions that can be described in wider encoding (e.g., 64-bit).
3. GPU-like capabilities like thread divergence and scheduling.
4. Memory-to-memory vector operations.
5. Sparse matrix support.
6. How to deal with incomplete/partial architectural specifications (e.g., unordered arithmetic operations).
7. Support for OCP Microscaling (MX) Formats.
8. Multiple vector multiply-accumulate instructions (e.g., Intel x86 V4-like instructions).
9. Video workloads [discussion](https://lists.riscv.org/g/sig-vector/topic/vector_operations_for_video/108187661) and [proposal](https://lf-rise.atlassian.net/wiki/spaces/HOME/pages/8588516/RISCV64+new+vector+instructions+requirements+for+video+multimedia).
10. Support for wireless workloads.
11. FP8 support, independent of MX Format.
12. [8-bit integer dot-product](https://github.com/riscv/riscv-dot-product/releases/download/v0.0.1/dot-product.pdf).
13. Mingled floating-point and vector register files.
14. Mask/shift instructions.
15. Olaf Bernstein's [Informal Gap Analysis](https://gist.github.com/camel-cdr/99a41367d6529f390d25e36ca3e4b626).
16. Punit Agrawal's [Vector Operations Proposal](https://lf-rise.atlassian.net/wiki/spaces/HOME/pages/145948673/Vector+Operations+Proposals+-+Draft+Document).


