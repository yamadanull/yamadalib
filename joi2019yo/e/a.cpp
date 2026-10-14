#include "../../template/template.hpp"
#include "../../segment-tree/segment-tree-beats.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N,M);
	vl A(N); in(A);
	vl L(N);
	{
		AngelBeats seg(N);
		seg.range_update(0,N,N);
		while(M--){
			inl(l,r); --l;
			seg.range_chmin(l,r,l);
		}
		rep(i,N)L[i]=seg.range_sum(i,i+1);
	}

	UpdateMax_LazySegmentTree<ll,-infLL> seg(vl(N,0));
	rep(i,N){
		ll ans=seg.query(0,L[i]);
		amax(ans,0);
		ans+=A[i];
		seg.update_val(i,ans);
	}
	out(seg.query());
}
