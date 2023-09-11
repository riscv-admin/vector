# Task Group: Attached Matrix Facility

## Charter

Develop the specification of an attached matrix facility ISA for RISC-V.
An attached matrix facility for RISC-V must support *scalable matrices*.
We can think of scalable matrices as the two-dimensional counterpart to scalable vectors.
Implementations must have the flexibility to choose the shape (number of rows and number of columns) of their matrix registers.
The specification could (and should) impose certain restrictions on that flexibility.
For example: maybe only square matrix registers should be allowed, or the number of rows and columns must be a power of 2.
The specification must support the development of *matrix size agnostic* code at the machine level.
A correctly written agnostic binary will produce the same result in any RISC-V processor that supports the attached matrix facility.

## Members

- Philipp Tomsich
