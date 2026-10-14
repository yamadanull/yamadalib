#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../dp/inversion-counting.hpp"

void yamada::solve()
{
	inl(N,M); ++N;
	const ll MXD=M*(M-1)/2;

	vl C(N); vv(ll,A,N,M);
	rep(i,M)A[0][i]=i+1;
	rep(i,1,N)in(C[i],A[i]);
	each(a,A)each(e,a)--e;

	UpdateMax_LazySegmentTree<ll,-infLL> seg(N);
	seg.set(0,0);
	rep(i,1,N){
		ll R=max(i-MXD,0LL);
		ll ans=(ll)seg.prod(0,R);
		if(ans>=0)ans+=C[i];
		rep(j,R,i){
			ll time=i-j;
			ll dist=swap_distance(A[i],A[j]);
			if(time>=dist){
				ll bns=seg[j];
				if(bns>=0)amax(ans,bns+C[i]);
			}
		}
		seg.set(i,ans);
	}
	out(seg.prod());
}
