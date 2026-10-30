#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(M,S=LL*(M/2));
	ll N=len(S);
	VV(ll,dp,N+1,M+1,infLL);
	dp[0][0]=0;
	rep(i,N)rep(j,M+1)if(dp[i][j]<infLL){
		amin(dp[i+1][j],dp[i][j]);
		if(j+S[i]<=M)amin(dp[i+1][j+S[i]],dp[i][j]+1);
	}
	auto ans=dp[N][M];
	out(ans);
	assert(ans==infLL||ans==2 || ans==3);
}
