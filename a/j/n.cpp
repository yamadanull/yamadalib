#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N,K); N+=2;
	vl A(N); rep(i,1,N-1)in(A[i]);
	AddMax_LazySegmentTree<ll,-infLL> seg(A);
	minpq<pl> q; // [len,L]

	while(K>0){
		vp lr;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && A[l]==A[r])++r;
			if(l>0 && r<N){
				if(A[l-1]<A[l] && A[l]>A[r]){
					lr.eb(l,r);
				}
			}
		}

		if(lr.empty())break;
		ll len=infLL;
		each2(l,r,lr)amin(len,r-l);
		each2(l,r,lr)if(len==r-l){
			ll dist=A[l]-max(A[l-1],A[r]);

			ll red=min(dist*len,K);
			ll red0=red/len;
			ll red1=red%len;
			rep(i,l,r)A[i]-=red0;
			rep(i,l,l+red1)A[i]-=1;
			K-=red;
			break;
		}
	}

	ll ans=0;
	rep(i,N-1)ans+=abs(A[i]-A[i+1]);
	out(ans);
}
