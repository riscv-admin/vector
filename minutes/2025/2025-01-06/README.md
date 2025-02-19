## Meeting details

Date: 2025-01-06
Time: 17:00 (CET), 08:00 (PDT), 11:00 (EDT)

Attendance (# people):

- Jose Moreira (Chair, IBM)
- Abel Bernabeu (Vice-chair, Esperanto)

## Disclaimer

- [Slides](https://docs.google.com/presentation/d/1LNhpuNwU54TgwGfcl-Fgf4HUFxCxh0AztPaeqMuRQRw/edit?pli=1#slide=id.p1)
- [Video](https://wiki.riscv.org/display/HOME/Meeting+Disclosures)

## Meeting Schedule

- We meet every other Monday, 11:00-12:00 ET
- Previous meetings:
- Current meeting: [2025-JAN-06](https://github.com/riscv-admin/vector/tree/main/minutes/2025/2026-01-06)
- Next meeting: 2025-JAN-20 (MLK Day)

## Agenda
- [Zoom recording]()
- [AI-generated summary]() - Use with caution!
- Happy New Year!
- Move to LFX meeting

### From last meeting
1. Three (possible) fast-track proposals
      1. Dot-product (already under way).
      2. Zip/unzip instructions.
      3. Absolute differences instructions. 
2. Conversion-only instructions for FP8 formats (focus on E5M2 and E4M3 element format).

### New issues raised during the Holidays
1. Inconsistency between published ISA and github?
      1. The official specification is the [RISC-V ISA Manual](https://github.com/riscv/riscv-isa-manual)
      2. Including the ["V" Standard Extension for Vector Operations, Version 1.0](https://github.com/riscv/riscv-isa-manual/blob/main/src/v-st-ext.adoc)
      3. The [RISC-V "V" Vector Extension](https://github.com/riscvarchive/riscv-v-spec/blob/master/v-spec.adoc) is *archived* (and stale)
2. Non-deterministic behavior? ((deterministic/nondeterministic) vs (undefined, under specified, implementation defined, statistically specified) vs (conforming/nonconforming)
