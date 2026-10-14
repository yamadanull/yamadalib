#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	min_segtree<ll> seg(A);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,x);
		}
		else{
			LL(l,r); --l;
			OUT(seg(l,r));
		}
	}
}
