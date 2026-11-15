#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,M,A=LL*N,BIND(B,C)=~PR(LL,LL)[N-1]);
	B.eb(0);
	C.eb(0);
	VV(ll,dp,N+1,M+1,-infLL);
	dp[0][M]=0;
	rep(i,N)rep(j,A[i],M+1)if(dp[i][j]>=0){
		ll J=min(j-A[i]+B[i],M);
		amax(dp[i+1][J],dp[i][j]);
		J=j-A[i];
		amax(dp[i+1][J],dp[i][j]+C[i]);
	}
	out(Max(dp[N]));
}
