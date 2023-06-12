## Meeting details

Date: 2023-06-12

Time:
- 23:00 (CST)
- 17:00 (CET)
- 08:00 (PDT)

Attendance (18 people):

- Abel Bernabeu (Vice-chair, Esperanto)
- Jeff Scheel (RISC-V)
- Jose Moreira (Chair, IBM)
- Al Martin (Akeana)
- Ken Dockser (Tenstorrent)
- Philipp Tomsich (VRull)
- Ali Zaidi (Tenstorrent)
- Bing Yu (Andes)
- Enis Mustafa (Individual)
- Fatima Saleem (10xEngineers)
- Guy Lemieux
- John Simpson (SiFive)
- Mark Himelstein (CTO, RISC-V)
- Qiu Jing (T-Head)
- Rafael Sene (Technical Program Manager, RISC-V)
- Victor Moya (Semidynamics)
- Yixuan Chen (PLCT)
- Nicolas Brunie

## Agenda

- Introductions
- Charter discussion
- Gap analysis discussion

## Introductions

Jose Moreira: introduces the group's purpose, describing the SIG as a group that will suggest the creation of task groups.

Abel Bernabeu: briefs his expected role assisting Jose Moreira and bringing for discussion use cases from the graphics and ML domains.

## Charter

Mark Himelstein: highlights the three actions he expects from the group.

1. Strategy definition.
2. Gap analysis
3. Prioritization

Mark's expectation is to have the gap analysis documented in three to four months.

He expects prioritization for picking the things we do and discarding the things we do not. And from members in the SIG he asks for involvement on the task groups.

Ken Dockser: takes the opportunity to ask for resources who write architectural compliance tests for the vector crypto extension. It is "just" 5 instructions awaiting for testing TLC.

Philipp Tomsich: highlights how the specification write up is just one part of the publishing process. Other tasks like prototyping, testing and technical review take even more resources than the write up.

Mark Himelstein: makes a call for the majority of that work to be delegated to the task groups.

Philipp Tomsich: asks whether the P extension depends on the group in any way.

Jose Moreira adds the term explicitly to the charter he was drafting.

Mark Himelstein: goes into talking a bit about the status of the P extension, and the current involvement of the Architectural Review Committee for the last year and a half. He does not think we need to create any group, but a mention on the strategy definition is actually expected from this SIG.

Ken Dockser: reminds us how the P and the vector extensions are mutually exclusive due to collision of opcodes.

Mark Himelstein: thinks the opcode collision is for the task groups (TGs) to deal with, and does not preclude the Vector SIG from including P in the planning.

Mark Himelstein does remind us that there is a preliminary charter we can modify, but in essence we are describing something very close to what he wrote (together with Krste Asanovic). There is a link to the charter he was talking about on the references.

## Gap Analysis

Jose Moreira: goes through a series of bullet points with gaps that he has initially gathered.

1. Self-contained specification of vector instructions behaviour
2. Handling of divergence of workitems on control flow bifurcation as seen in GPUs (and projects like Vortex or Ventus if specifically looking at the RISC-V landscape).
3. Matrix multiply
4. Coprocessor interfaces (opcodes and instruction formats at architectural level and buses at microarchitectural level).

This last point is a bit controversial with two valid points made that will require further clarification.

Philipp Tomsich: buses are microarchitecture and therefore out of scope.

Mark Himelstein: co-processors is a general subject that is not vector/SIMD specific.

Guy Lemieux: shows interest in coprocessors, seeing the concept as a testbench for new features. Would like to see some planning ahead in this area.

Mark Himelstein and Philipp Tomsich name some gaps they collected from talking to different people:

- More reduced sets of Zv features for embedded profiles, following up the work done in Zve. Not for simplicity of implementation, but for area reduction.
- Streaming of data.
- Getting the mask support close to the concept of predication, likely adding extra mask registers. This needs to be followed up with Allen Baum from Esperanto, who is interested in getting this feature for backporting the software they wrote for their custom vector extension.

Abel Bernabeu suggests allocating the support for instruction predication on the same task group as the handling of divergence on work items, earlier mentioned by Jose Moreira.

## To be continued...
Before closing, Jose Moreira (chair) commits to continuing the discussion on supporting custom extensions, apologizing for having had to interrupt Guy Lemieux.

## References

- Preliminary charter for the Vector SIG

URL: [https://github.com/riscv-admin/vector/blob/main/CHARTER.md](https://github.com/riscv-admin/vector/blob/main/CHARTER.md)

- Vortex's official website

URL: https://vortex.cc.gatech.edu/

- Ventus' official website

URL: https://github-com.translate.goog/THU-DSP-LAB/ventus-gpgpu/blob/master/docs/Ventus-GPGPU-doc.md?_x_tr_sl=zh-CN&_x_tr_tl=en&_x_tr_hl=en&_x_tr_pto=sc

- Stream Semantic Registers: A Lightweight RISC-V ISA Extension Achieving Full Compute Utilization in Single-Issue Cores

URL: https://arxiv.org/abs/1911.08356

- Vector SIG's GitHub repo

URL: https://github.com/riscv-admin/vector
