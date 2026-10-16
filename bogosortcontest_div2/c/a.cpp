#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(S=STR,K);
	ll N=len(S);
	vl fn(N);
	rep(i,N-2){
		if(S[i]==S[i+2])fn[i]=1;
	}
	vl gn(N+1);
	rep(i,3,N+1)gn[i]=fn[i-3];
	CumulativeSum cumg(gn);
	ll ans=0;
	rep(l,N-2)if(fn[l]){
		ll rr=l+K+1;
		amin(rr,N+1);
		ll rl=l+3;
		if(rl<rr)ans+=cumg(rl,rr);
	}
	out(ans);
}
