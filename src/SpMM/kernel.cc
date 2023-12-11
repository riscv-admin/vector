#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<vector>
#include<array>

using namespace std;

template <typename T, size_t N, size_t M>
class svector
{
    private:

	array<T, M>	_data;	// values of nonzero elements (at most M)
	array<bool, N>	_mask;	// mask of nonzero elements (at most M 1's)

    public:

	size_t popcount() const	// returns number of 1's in mask
	{
	    size_t cnt = 0;
	    for (size_t i=0; i<N; i++) if (_mask[i]) cnt++;
	    return cnt;
	}

	const array<bool, N>	&mask() const
	{
	    return _mask;
	}

	const T& operator()(size_t i) const
	{
	    assert(i < M);
	    return _data[i];
	}
};

template <typename T, size_t N, size_t M>
class smatrix
{
    private:

	array<array<T,M>, N>	_data;	// N columns, each with at most M nonzeroes
	array<bool, N>		_mask;	// mask of nonzero rows (at most M 1's)

    public:

	smatrix(const array<bool, N> &mask) : _mask(mask)
	{
	}

	size_t popcount() const	// returns number of 1's in mask
	{
	    size_t cnt = 0;
	    for (size_t i=0; i<N; i++) if (_mask[i]) cnt++;
	    return cnt;
	}

	const array<bool, N>	&mask() const
	{
	    return _mask;
	}

	T& operator()(size_t i, size_t j)
	{
	    assert(i < M);
	    assert(j < N);
	    return _data[j][i];
	}

	const T& operator()(size_t i, size_t j) const
	{
	    assert(i < M);
	    assert(j < N);
	    return _data[j][i];
	}
};

template <typename T, size_t N>
using dvector = array<T, N>;

template <typename T, size_t N, size_t M>
void operator+=
(
    array<T, N*N>		&D,	// Dense accumulating matrix
    const smatrix<T, N, M>	&S	// Sparse matrix
)
{
    assert(S.popcount() <= M);

    size_t row = 0;
    for (size_t i=0; i<N; i++)
    {
	if (S.mask()[i])
	{
	    for (size_t j=0; j<N; j++) { D[i*N+j] += S(row,j); }
	    row++;
	}
    }
}

template <typename T, size_t N, size_t M>
smatrix<T, N, M> operator*
(
    const svector<T, N, M> 	&a, 
    const dvector<T, N>		&b
)
{
    assert(a.popcount() <= M);

    smatrix<T, N, M>	r(a.mask());
    for (size_t i=0; i<M; i++) for (size_t j=0; j<N; j++)
    {
	r(i,j) = a(i) * b[j];
    }

    return r;
}

template<size_t N, size_t M>
void xf64mspvvmadd
/*
 * extended double-precision matrix, sparse-vector, vector multiply-add
 */
(
    array<double, N*N>		&C,	// Result accumulating matrix, shape NxN, dense
    const svector<double, N, M>	&a,	// Input N-element sparse vector, at most M nonzeroes
    const dvector<double, N>	&b	// Input N-element dense vector
)
{
    C += a*b;
}

template <size_t N, size_t M>
void DSpMM_kernel
/*
 * Computes the double-precisions sparse-matrix x dense-matrix multiplication
 *
 * 	C = C + A x B
 *
 * with
 *     C : square panel of size N x N
 *     A : vector of N-element sparse columns, each column with at most M nonzeros
 *     B : vector of N-element dense rows
 */
(
    array<double, N*N>			&C,	// Result panel, shape N x N, dense
    vector<svector<double, N, M> >	&A,	// Input panel, shape N x n, sparse
    vector<dvector<double, N> >		&B,	// Input panel, shape n x N, dense
    size_t				 n	// # of columns of A and rows of B to use
)
{
    assert(A.size() >= n);
    assert(B.size() >= n);

    // For each column of A and corresponding row of B
    for (size_t k=0; k<n; k++)
    {
	// Perform an "extended double-precision matrix, sparse-vector, vector multiply-add"
	xf64mspvvmadd(C, A[k], B[k]);
    }

    // Done!
    return;
}

template void DSpMM_kernel<8, 4>(array<double, 8*8>&, vector<svector<double, 8, 4> >&, vector<dvector<double, 8> >&, size_t);
