#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	ll ans=1;
	rep(l,N)rep(r,l+1,N){
		ll d=(A[r]-A[l])/(r-l);
		auto check=[&](ll i)->bool{ return(i-l)*d+A[l]==A[i]; };
		if(!check(r))continue;
		ll k=K;
		rep(i,l,r)if(!check(i))--k;
		if(k<0)continue;
		ll bns=r-l+1;
		bns+=k;
		amin(bns,N);
		amax(ans,bns);
	}
	out(ans);
}
