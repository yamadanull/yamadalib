#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,Q);
	vc<array<ll,3>> lrc(N); in(lrc);
	each3(l,r,c,lrc)--l;
	while(Q--){
		inl(I,J); --I; --J;
		ll ans=-1;
		rep(msk,1<<N){
			if(!(msk>>I&1))continue;
			if(!(msk>>J&1))continue;
			ll bns=0;
			vl cnt(N);
			rep(i,N)if(msk>>i&1){
				auto[l,r,c]=lrc[i];
				rep(d,l,r)++cnt[d];
				bns+=c;
			}
			if(Max(cnt)<=1)amax(ans,bns);
		}
		out(ans);
	}
}
