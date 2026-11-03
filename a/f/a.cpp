#include "../../template/multitest-template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(N,M);
	VV(mint,dp,N+1,M+3);
	rep(i,N){
		dp[i+1][2]+=1;
		CumulativeSum cum(dp[i]);
		rep(j,2,M+3){
			ll l=j+2>>1;
			ll r=j;
			dp[i+1][j]+=cum(l,r+1);
		}
	}
	out(dp[N][M+2]);
}
