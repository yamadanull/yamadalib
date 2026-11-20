#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(N,K);
	N*=2;
	K-=N/2;
	K=N*(N-1)/2-K;
	if(K<0||K>N*(N-1)/2)DIE(0);
	VVV(mint,dp,N+1,N/2+1,K+1);
	dp[0][0][0]=1;
	rep(n,N)rep(c,n/2+1)rep(s,K+1)if(dp[n][c][s]!=0){
		dp[n+1][c][s]+=dp[n][c][s];
		if(s+n<=K)dp[n+1][c+1][s+n]+=dp[n][c][s]*(N/2-c)*(n-c*2);
	}
	out(dp[N][N/2][K]);
}
