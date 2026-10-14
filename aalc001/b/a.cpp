#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	addmin_lazyseg<ll> seg(A);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(l,r,x); l--;
			seg.apply(l,r,x);
		}
		else{
			LL(l,r); --l;
			OUT(seg(l,r));
		}
	}
}
