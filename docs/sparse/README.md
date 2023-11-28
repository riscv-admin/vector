# Sparse Linear Algebra

Jose Moreira, IBM Research

## Introduction

*Sparse linear algebra is not linear algebra with lots of zeroes.*
Sparse linear algebra has its own structure and definitions, meant to directly operate on *sparse matrices*.
A sparse matrix $`\mathbf{A} = \left\langle D, M, N, \{(i,j,A_{ij})\} \right\rangle`$ is defined by
a domain $D$, its number of rows $M > 0$, its number of columns $N > 0$, and a set of tuples
$(i \in \mathbb{Z} \cap [0,M), j \in \mathbb{Z} \cap [0,N), A_{ij} \in D)$.
A particular pair of values $i,j$ can appear at most once in $\mathbf{A}$. 
The set $`\mathbf{L}(\mathbf{A}) = \{(i,j,A_{ij}\}`$ is called the *content* of matrix $\mathbf{A}$.
(If we were dealing exclusively with sparse matrices, $\mathbf{L}(\mathbf{A})$ would uniquely define $\mathbf{A}$.
Because we will operate with both sparse and dense matrices, we need the $M$ and $N$ parameters.)

Example: consider the matrix
```math
\mathbf{A} = \left\langle \mathbb{R}, 4, 3, \left\{ (0, 0, 1.0), (0, 2, 0.5), (1, 1, 3.1), (2, 0, 2.0), (2, 1, 1.0), (3,2, 5.0) \right\} \right\rangle.
```
The visual representation of this matrix would be the following:
```math
\left[
\begin{array}{ccc}
1.0   &      & 0.5   \\
      & 3.1  &       \\
2.0   & 1.0  &       \\
      &      & 5.0
\end{array}
\right]
```
*Important*: The "missing" values in the contents of the matrix are not "0", they simply *do not exist*.
