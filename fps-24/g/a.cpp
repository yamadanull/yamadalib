#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N,M,L);
	// i円まで自由に使える
	V<mint> dp(N+1);
	dp[0]=1;
	rep(i,1,M+1){
		// i円硬化追加
		rep(j,N-i+1)dp[j+i]+=dp[j];

		if(i>=L+1){
			// m=i-L円効果削除
			ll m=i-L;
			auto ep=dp;
			rep(j,N+1-m)ep[j+m]-=dp[j];
			dp=ep;
		}
		if(i>=L){
			out(dp.back());
		}
		/* out(i,":",dp); */
	}
}
