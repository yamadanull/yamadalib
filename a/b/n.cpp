#include "../../template/template.hpp"
using namespace yamada;

vint naive(ll N,ll K){
	vint ans;
	nxp(N,[&](auto A){
		if(!ans.empty())return;
		ll x=0;
		rep(i,N){
			x|=A[i]&i;
		}
		if(x==K)ans=A;
	});
	return ans;
}

void yamada::solve()
{
	IN(N);

	rep(n,1,N+1)rep(k,infLL){
		if(msb(n-1)<msb(k))break;
		auto ans=naive(n,k);
		/* err(n,k,ans); */
		if(ans.empty()){
			err(n,k);
		}
	}
}
