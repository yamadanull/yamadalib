#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	ll M=1<<20;
	vc<mint> dp(M);
	vc<mint> ep(M);
	vc<mint> pw(M,1);
	rep(i,1,M)pw[i]=pw[i-1]*2;
	rep(i,2,M-1){
		ep[i+1]+=ep[i]*pw[i-1]*pw[i+1];
		ep[i+1]+=pw[i-1]*(pw[i-1]-1)*binom.inv(2)*pw[i+1];
		ep[i+1]+=(pw[i-1]-1)*pw[i];
		dp[i+1]+=ep[i]*pw[i-1];
		dp[i+1]+=pw[i-1]*(pw[i-1]+1)*binom.inv(2)-1;
	}

	IN(T);
	while(T--){
		IN(n);
		out(dp[n]+1);
	}
}
