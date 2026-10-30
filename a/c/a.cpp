#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,C,A=--LL*N);
	out(bisect<ll>(1<<30,0,[&](ll K)->bool{
		/* err(K); */
		vl B;
		rep(i,N){
			if(i>0 && A[i-1]+K>=A[i])continue;
			if(i<N-1 && A[i]+K>=A[i+1])continue;
			B.eb(i);
		}

		ll n=len(B);
		ll ans=0;
		for(ll l=0,r=0; l<n; l=r){
			while(r<n && B[l]+(r-l)==B[r])++r;
			ll L=B[l];
			ll R=B[r-1]+1;
			rep(i,L,R){
				if(i<R-1){
					ll d=A[i+1]-A[i];
					if(d<=K*2)++i;
				}
				++ans;
			}
		}
		return ans<=C;
	}));
}
