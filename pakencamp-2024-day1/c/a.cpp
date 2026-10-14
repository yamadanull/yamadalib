#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	AddSum_LazySegmentTree<ll> seg(A);
	inl(Q);
	while(Q--){
		inl(l,r); --l;
		ll bord=seg.query(l,r)/2;
		/* out(bord); */
		ll ans=seg.max_right(l,[&](ll sum){return sum<=bord;})+1;
		out(ans);
	}
}
