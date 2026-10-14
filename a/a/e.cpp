#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,K);
	// sum:i group:k
	vv(ll,dp,N+1,K+1);
	dp[1][1]=1;
	rep(i,1,N+1)rep(k,1,K+1){
		dp[i][k]+=dp[i][k-1];
		if(i-k>=1)dp[i][k]+=dp[i-k][k];
	}
	out(dp[N][K]);
}
