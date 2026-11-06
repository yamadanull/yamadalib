#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,BIND(L,R)=~PR(--LL,--LL)[N-1]);
	L.insert(L.begin(),0);
	R.insert(R.begin(),0);

	vvl Rinv(N);
	rep(u,N)Rinv[R[u]].eb(u);

	updatesum_lazyseg<ll> seg(vl(N,1));
	ll ans=0;
	rep(i,N){
		if(i>0)seg.apply(L[i],R[i]+1,0);
		each(u,Rinv[i]){
			ans+=seg(L[u],R[u]+1);
		}
	}
	out(ans-1);
}
