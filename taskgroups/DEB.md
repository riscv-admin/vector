# Task Group: Direct Encoding of Behavior

## Charter

Develop the specification of a more direct encoding version of RISC-V vector instructions.
We realize that, in a scalable vector architecture, some configuration registers will be always necessary.
For example, the vector length cannot be directly encoded in the instruction, otherwise the code would not be *vector length agnostic*.
There is a clear distinction between *global properties* (e.g., vector length) and *local properties* (e.g., element width).
We do not want to prescript or limit the solutions the Task Group will investigate, but we believe that it would be advantageous to directly encode the local properties on each instruction, while leaving the global properties for the control registers.
An additional impact of this work could include supporting the explicit identification of a mask register in each vector instruction.

## Members

- Guido Araujo
