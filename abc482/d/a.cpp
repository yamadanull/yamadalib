#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,X=LL*N);
	if(N==1)DIE(0);
	rep(k,N){
		ll ans=infLL;
		ll x=X[k];
		if(k>0){
			ll bns=-infLL;
			ll x_1=X[k-1];
			amax(bns,X.back()-x_1>>1);
			amax(bns,x-X.front()>>1);
			err(k,ans,bns);
			amin(ans,bns);
		}
		if(k<N-1){
			ll bns=-infLL;
			amax(bns,X.back()-x>>1);
			ll x1=X[k+1];
			amax(bns,x1-X.front()>>1);
			err(k,ans,bns);
			amin(ans,bns);
		}
		out(ans);
	}
}
