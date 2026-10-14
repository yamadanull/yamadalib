#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	const ll log=30;
	vv(ll,dp,log,N);
	rep(i,N)rep(t,log){
		if(A[i]>>t&1){
			if(B[i]>>t&1)dp[t][i]=0; // 1->1
			else die(-1); // 1->0
		}
		else{
			if(B[i]>>t&1)dp[t][i]=-1; // 0->1
			else dp[t][i]=1; // 0->0
		}
	}

	ll ans=0;
	rep(t,log){
		for(ll l=0,r=0; l<N; l=r){
			if(dp[t][l]>=0){ ++r; continue; }
			while(r<N && dp[t][r]!=1)++r;
			if(dp[t][l])ans+=1LL<<t;
		}
	}
	out(ans);
}
