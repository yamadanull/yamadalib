#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	LL(N,Q);
	vl A(N); IN(A);
	sum_segtree<ll> seg(A);
	FOR(Q){
		LL(op);
		if(op==1){
			LL(i,x); --i;
			seg.set(i,x);
		}
		else if(op==2){
			LL(l,t); --l;
			auto ans=seg.max_right(l,[&](ll sm){return sm<t;})+1;
			OUT(ans);
		}
		else{
			LL(r,t);
			auto ans=seg.min_left(r,[&](ll sm){return sm<t;})-1;
			OUT(ans+1);
		}
	}
}
