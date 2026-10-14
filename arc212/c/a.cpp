#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,M); N-=M;
	if(N<0)die(0);
	V<mint> dp(N+1),ep(N+1);
	rep(i,N+1){
		if(i%2==0){
			dp[i]=binom.H(M,i/2);
		}
		ep[i]=binom.H(M*2,i);
	}
	/* out(dp); */
	/* out(ep); */
	mint ans=0;
	rep(i,N+1)ans+=dp[i]*ep[N-i];
	ans*=((mint)2).pow(M);
	out(ans);
}
