#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,K,A=LL*N);
	vl R(N);
	for(ll l=0,r=0;l<N;l=r){
		while(r<N&&A[l]==A[r])++r;
		rep(i,l,r)R[i]=r;
	}
	ll ans=0;
	rep(i,K){
		if(R[i]>=N-K+i+1)++ans;
	}
	out(ans);
}
