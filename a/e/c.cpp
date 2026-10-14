#include "../../template/multitest-template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../multiplicative-function/mf-famous-series.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;

mint naive(ll N,ll M,ll K){
	// gcdがiの倍数であるものの数
	vc<mint> dp(M+1);
	rep(g,1,M+1){
		dp[g]=mint(M/g).pow(N);
	}

	auto mob=mobius_function<mint>(M+1);
	vc<mint> ep(M+1);
	rep(g,1,M+1){
		rep(G,g,M+1,g){
			ep[g]+=mob[G/g]*dp[G];
		}
	}
	mint ans=0;
	rep(g,1,M+1)ans+=ep[g]*(mint(g).pow(K));
	return ans;
}

void yamada::solve()
{
	inl(N,M,K);

	out(naive(N,M,K));
}
