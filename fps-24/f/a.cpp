#include "../../template/template.hpp"
#include "../../matrix/matrix-fast.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using mat=Matrix<mint,4,4>;
void yamada::solve()
{
	inl(N);
	mat A;
	rep(i,4)rep(j,4)A[i][j]=(i+j==3? 0:1);
	A^=N;
	out(A[0][1]);
}
