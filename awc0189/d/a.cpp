#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,K,D,A=LL*N);
	VV(ll,dp,N+1,K+1,-infLL);
	dp[0][0]=0;
	rep(i,N)rep(j,K+1)if(dp[i][j]>=0){
		amax(dp[i+1][j],dp[i][j]);
		if(j<K){
			ll I=min(N,i+D+1);
			amax(dp[I][j+1],dp[i][j]+A[i]);
		}
	}
	out(Max(dp.back()));
}
