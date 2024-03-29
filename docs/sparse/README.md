# Sparse Linear Algebra

Jose Moreira, IBM Research

---
> "Though a bit of an exageration, it can be said that a mathematical problem can be solved only if it can be reduced to a calculation in linear algebra." — *Thomas A. Garrity*, All the Math You Missed
---

## Introduction

*Sparse linear algebra is not linear algebra with lots of zeroes.*
Sparse linear algebra has its own structure and definitions, meant to directly operate on various sparse data structures.
We define those sparse data structures and their more traditional dense counterparts.
We also define the various operations that can be performed on sparse data structures, including operations that
mix dense and sparse data structures.
The objective is to create a computational model that can be supported by a specialized instruction set architecture.

## Notation

- $\mathbb{R}$ : The set of real numbers.
- $\mathbb{Z}$ : The set of integer numbers.
- $[a,b)$ : The set $`\{ x \in \mathbb{R} : a \leq x < b\}`$

## Dense vectors and matrices
For completeness, we start with the definition of the more traditional dense data structures used in linear algebra.

A dense vector $`\mathbf{v} = \left\langle D, N, v[0:N-1] \right\rangle`$ is defined
by a domain $D$, its number of elements $N > 0$, and an one-dimensional
array of elements $v[i] \in D$, $i \in \mathbb{Z} \cap [0,N)$.

> Example: consider the dense vector
> ```math
> \mathbf{v} = \left\langle \mathbb{R}, 4,
> \left[
> \begin{array}{c}
> 1.0   \\
> 0.0   \\
> 2.0   \\
> 0.0   
> \end{array}
> \right]
> \right\rangle
> ```

A dense matrix $`\mathbf{A} = \left\langle D, M, N, A[0:M-1,0:N-1] \right\rangle`$ is defined
by a domain $D$, its number of rows $M > 0$, its number of columns $N > 0$, and a two-dimensional
rectangular array of elements $A[i,j] \in D$, $i \in \mathbb{Z} \cap [0,M), j \in \mathbb{Z} \cap [0,N)$.

> Example: consider the dense matrix
> ```math
> \mathbf{A} = \left\langle \mathbb{R}, 4, 3,
> \left[
> \begin{array}{ccc}
> 1.0   & 0.0  & 0.5   \\
> 0.0   & 3.1  & 0.0   \\
> 2.0   & 1.0  & 0.0   \\
> 0.0   & 0.0  & 5.0
> \end{array}
> \right]
> \right\rangle
> ```

The $i$-th row of a dense matrix $\mathbf{A} = \left\langle D, M, N, A[0:M-1,0:N-1] \right\rangle$, $i \in \mathbb{Z} \cap [0,M)$ 
is a dense vector represented as $\mathbf{A}_i$ and defined as
```math
\mathbf{A}_i = \left\langle D, N, A[i, 0:N-1] \right\rangle.
```

The $j$-th column of a dense matrix $\mathbf{A} = \left\langle D, M, N, A[0:M-1,0:N-1] \right\rangle$, $j \in \mathbb{Z} \cap [0,N)$ 
is a dense vector represented as $\mathbf{A}^j$ and defined as
```math
\mathbf{A}^j = \left\langle D, M, A[0:M-1, j] \right\rangle.
```

## Sparse vectors and matrices
*A sparse vector is not a dense vector with lots of zeroes.*
A sparse vector $`\mathbf{v} = \left\langle D, N, \{(i,v_{i})\} \right\rangle`$ is defined by
a domain $D$, its number of elements $N > 0$, and a set of tuples
$(i \in \mathbb{Z} \cap [0,N), v_{i} \in D)$.
A particular value $i$ can appear at most once in $\mathbf{v}$. 
The set $`\mathbf{L}(\mathbf{v}) = \{(i,v_{i})\}`$ is called the *content* of vector $\mathbf{v}$.
(If we were dealing exclusively with sparse vectors, $\mathbf{L}(\mathbf{v})$ would uniquely define $\mathbf{v}$.
Because we will operate with both sparse and dense vectors, we need the $N$ parameter.)
The set $`\mathbf{I}(\mathbf{v}) = \{ i : (i,v_i) \in \mathbf{L}(\mathbf{v}) \}`$ is called the *index set* of vector $\mathbf{v}$.

> Example: consider the sparse vector
> ```math
> \mathbf{v} = \left\langle \mathbb{R}, 4, \left\{ (0, 0, 1.0), (2, 0, 2.0) \right\} \right\rangle.
> ```
> The visual representation of this matrix would be the following:
> ```math
> \mathbf{v} = 
> \left[
> \begin{array}{c}
> 1.0   \\
>       \\
> 2.0   \\
>       
> \end{array}
> \right]
> ```
> *Important*: The "missing" values in the contents of the vector are not "0", they simply *do not exist*.

*A sparse matrix is not a dense matrix with lots of zeroes.*
A sparse matrix $`\mathbf{A} = \left\langle D, M, N, \{(i,j,A_{ij})\} \right\rangle`$ is defined by
a domain $D$, its number of rows $M > 0$, its number of columns $N > 0$, and a set of tuples
$(i \in \mathbb{Z} \cap [0,M), j \in \mathbb{Z} \cap [0,N), A_{ij} \in D)$.
A particular pair of values $i,j$ can appear at most once in $\mathbf{A}$. 
The set $`\mathbf{L}(\mathbf{A}) = \{(i,j,A_{ij})\}`$ is called the *content* of matrix $\mathbf{A}$.
(If we were dealing exclusively with sparse matrices, $\mathbf{L}(\mathbf{A})$ would uniquely define $\mathbf{A}$.
Because we will operate with both sparse and dense matrices, we need the $M$ and $N$ parameters.)

> Example: consider the sparse matrix
> ```math
> \mathbf{A} = \left\langle \mathbb{R}, 4, 3, \left\{ (0, 0, 1.0), (0, 2, 0.5), (1, 1, 3.1), (1, 2, 0.0), (2, 0, 2.0), (2, 1, 1.0), (3,2, 5.0) \right\} \right\rangle.
> ```
> The visual representation of this matrix would be the following:
> ```math
> \mathbf{A} = 
> \left[
> \begin{array}{ccc}
> 1.0   &      & 0.5   \\
>       & 3.1  & 0.0   \\
> 2.0   & 1.0  &       \\
>       &      & 5.0
> \end{array}
> \right]
> ```
> *Important*: The "missing" values in the contents of the matrix are not "0", they simply *do not exist*.

The definition above is orthogonal to and independent of the data structures used to represent sparse matrices.
Standard sparse data structure formats, such as COO, CSR, and CSC, can all be used to represent sparse matrices as defined above.

The $k$-th row    of a sparse matrix $\mathbf{A} = \left\langle D, M, N, \{(i,j,A_{ij})\} \right\rangle$, $k \in \mathbb{Z} \cap [0,M)$ 
is a sparse matrix represented as $\mathbf{A}_k$ and defined as
```math
\mathbf{A}_k = \left\langle D, N, \{(k,j,A_{kj}) \in \mathbf{L}(\mathbf{A}) \} \right\rangle.
```

The $k$-th column of a sparse matrix $\mathbf{A} = \left\langle D, M, N, \{(i,j,A_{ij})\} \right\rangle$, $k \in \mathbb{Z} \cap [0,N)$ 
is a sparse matrix represented as $\mathbf{A}^k$ and defined as
```math
\mathbf{A}^k = \left\langle D, M, \{(i,k,A_{ik}) \in \mathbf{L}(\mathbf{A}) \}  \right\rangle.
```

## Semirings

Operations on sparse matrices, including sparse matrix/dense vector- and sparse matrix/dense matrix-multiplication (SpMV and SpMM) are defined on a *semiring*.
A semiring $`S = \left\langle D, \oplus, \otimes, \mathbf{0}, \mathbf{1} \right\rangle`$ is defined by a domain $D$, 
a binary commutative additive operation $\oplus : D \times D \rightarrow D$, a binary multiplicative operation $\otimes: D \times D \rightarrow D$, a semiring addititve identity (SAID) $\mathbf{0} \in D$ ($a \oplus \mathbf{0} = \mathbf{0} \oplus a = a, \forall a \in D$)
that is also the multiplicative anihalator ($a \otimes \mathbf{0} = \mathbf{0} \otimes a = \mathbf{0}, \forall a \in D$), and a semiring multiplicative identity (SMID) $\mathbf{1} \in D$ ($a \otimes \mathbf{1} = \mathbf{1} \otimes a = a, \forall a \in D$).
The multiplicative operation $\otimes$ distributes over the additive operation $\oplus$.

> Example:
> 
> In the common arithmetic semiring $`\left\langle \mathbb{R}, +, \times, 0, 1 \right\rangle`$, the additive and multiplicative operations are the usual plus and times of real numbers, and the real values 0 and 1 are the SAID and SMID, respectively.
> In the min-max semiring $`\left\langle \mathbb{R}, \min(\cdot,\cdot), \max(\cdot,\cdot), +\infty, -\infty \right\rangle`$, the additive operation is the minimum of two real numbers, 
> the multiplicative operation is the maximum of two real numbers, the SAID is $+\infty$ and the SMID is $-\infty$.

The definition of semiring explains why one cannot transform a sparse matrix to a dense matrix by filling the "missing" elements with 0.
The value of the SAID is a property of the semiring, not the matrix, and is not known until operation time. The sparse matrix must be represented as a sparse matrix all the way up to and including any operation performed on it. We will explain why converting sparse matrices to dense matrices do not lead to the same computational outcome.

## Sparse/dense vector-outer product

Let $`\mathbf{u} = \left\langle D, M, \{(i,u_{i})\} \right\rangle`$ be a sparse vector.
Let $`\mathbf{v} = \left\langle D, N, v[0:N-1] \right\rangle`$ be a dense vector.
Let $`S = \left\langle D, \oplus, \otimes, \mathbf{0}, \mathbf{1} \right\rangle`$ be a semiring.
The *outer product* $\mathbf{u} \otimes \mathbf{v}$ of vectors $\mathbf{u}$ and $\mathbf{v}$ on semiring $S$ is a 
sparse matrix defined as
```math
\mathbf{u} \otimes \mathbf{v} = \left\langle D, M, N, \{(i, j, u_{i} \otimes v[j]) : \forall (i,u_{i}) \in \mathbf{L}(\mathbf{u}), \forall j \in \mathbb{Z} \cap [0,N) \} \right\rangle.
```
> Example:
>
> If 
> ```math
> \mathbf{u} = \left\langle \mathbb{R}, 4,
> \left[
> \begin{array}{c}
> u_0   \\
>       \\
> u_2   \\
>    
> \end{array}
> \right]
> \right\rangle
> ,
> \mathbf{v} = \left\langle \mathbb{R}, 3,
> \left[
> \begin{array}{c}
> v_0   \\
> v_1   \\
> v_2   
> \end{array}
> \right]
> \right\rangle
> ,
> S = \left\langle \mathbb{R}, +, \times, 0, 1 \right\rangle
> ```
> then
> ```math
> \mathbf{u} \otimes \mathbf{v} = \left\langle \mathbb{R}, 4, 3,
> \left[
> \begin{array}{ccc}
> u_0 v_0  & u_0 v_1  & u_0v_2  \\
>          &          &         \\
> u_2 v_0  & u_2 v_1  & u_2v_2  \\
>          &          &
> \end{array}
> \right]
> \right\rangle
> ```
> *Important*: No operations are performed with elements $u_1$ and $u_3$, since they do not exist.
> This bypasses the problem of having to deal with infinities and NaNs in floating-point numbers.

## Dense/sparse rank-1 update

Let $`\mathbf{A} = \left\langle D, M, N, A[0:M-1,0:N-1] \right\rangle`$ be a dense matrix.
Let $`\mathbf{u} = \left\langle D, M, \{(i,u_{i})\} \right\rangle`$ be a sparse vector.
Let $`\mathbf{v} = \left\langle D, N, v[0:N-1] \right\rangle`$ be a dense vector.
Let $`S = \left\langle D, \oplus, \otimes, \mathbf{0}, \mathbf{1} \right\rangle`$ be a semiring.
The *rank-1 update* $\mathbf{A} \oplus (\mathbf{u} \otimes \mathbf{v})$ of matrix $\mathbf{A}$ by vectors $\mathbf{u}$ and $\mathbf{v}$ on semiring $S$ is a 
dense matrix $\mathbf{C}$ defined as
```math
\mathbf{C} = \mathbf{A} \oplus (\mathbf{u} \otimes \mathbf{v}) = \left\langle D, M, N, C[i,j] = \left\{
\begin{array}{ll}
A[i,j] \oplus (u_i \otimes v_j) & \forall i \in    \mathbf{I}(\mathbf{u}) \\
A[i,j]                          & \forall i \notin \mathbf{I}(\mathbf{u})
\end{array}
\right\}, \forall j \in \mathbb{Z} \cap [0,N) \right\rangle.
```

## Sparse/dense generalized matrix-multiply

Let $`\mathbf{C} = \left\langle D, M, N, C[0:M-1,0:N-1] \right\rangle`$ be a dense matrix.
Let $`\mathbf{A} = \left\langle D, M, K, \{(i,j,A_{ij})\} \right\rangle`$ be a sprse matrix.
Let $`\mathbf{B} = \left\langle D, K, N, B[0:K-1,0:N-1] \right\rangle`$ be a dense matrix.
Let $`S = \left\langle D, \oplus, \otimes, \mathbf{0}, \mathbf{1} \right\rangle`$ be a semiring.
The *generalized matrix-multiply* $\mathbf{C} \oplus \mathbf{A} \otimes . \oplus \mathbf{B}$ of matrices $\mathbf{C}$, $\mathbf{A}$, and $\mathbf{B}$
is a dense matrix $\mathbf{R}$ defined as
```math
\mathbf{R} = \mathbf{C} \oplus (\mathbf{A}^0 \otimes \mathbf{B}_0) + (\mathbf{A}^1 \otimes \mathbf{B}_1) + \cdots + (\mathbf{A}^{K-1} \otimes \mathbf{B}_{K-1}).
```

## Consequences of this formulation of sparse linear algebra

1. *Separation of data and operations*: A sparse vector or matrix is represented in a way that is independent of any semiring used to operate on it. 
For example, matrices $`\mathbf{A} = \left\langle D, M, K, \{(i,j,A_{ij})\} \right\rangle`$ and $`\mathbf{B} = \left\langle D, K, N, B[0:K-1,0:N-1] \right\rangle`$
can be mulitplied using either $`\left\langle \mathbb{R}, +, \times, 0, 1 \right\rangle`$ semiring or $`\left\langle \mathbb{R}, \min(\cdot,\cdot), \max(\cdot,\cdot), +\infty, -\infty \right\rangle`$ semiring,
producing two different results.

1. *Difference between sparse and matrix operations*: Treating a sparse vector or matrix as a dense vector with the "missing" elements filled by the SAID will produce different results.
In particular, the result of the outer product of two dense vectors is a dense matrix. The result of the outer product of a sparse and a dense vector is a sparse matrix.
This difference is even more significant when operating in IEEE floating-point and the dense vector has infinities or NaNs. Those values are propagated with dense operations in a way that simply does not happen with sparse operations.
(The fundamental issue is that floating-point arithmetic is not a semiring. Among other problems, $0 \times \mbox{\sf NaN} = \mbox{\sf NaN} \neq 0$, so $0$ is not the multiplicative anihalator.
Similar issues arise in a min-max semiring with floating-point numbers.
Nevertheless, IEEE floating-point is a requirement in any modern computer architecture.)
