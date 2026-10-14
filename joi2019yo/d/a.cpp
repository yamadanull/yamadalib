#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	{
		++N;
		A.eb(0);
		auto B=mkuni(A);
		each(a,A)a=lb(B,a);
	}

	AddMax_LazySegmentTree<ll,-infLL> seg(vl(N,0));
	rep(i,N-1)if(A[i]>A[i+1]){
		seg.update(A[i+1],A[i],1);
	}
	out(seg.query());
}
