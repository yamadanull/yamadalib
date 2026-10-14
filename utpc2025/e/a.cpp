#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N);
	vl A(N); in(A); each(a,A)--a;
	AddSum_LazySegmentTree<mint> seg(V<mint>(N,0));
	seg.apply(A[0],A[0]+1,mint(1));
	rep(i,1,N){
		mint sum=seg.prod();
		sum-=seg[A[i]];
		seg.apply(A[i],A[i]+1,sum);
	}
	out(seg.prod());
}
