#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
mint pw2(ll a){ return ((mint)2).pow(a); }
mint pw2i(ll a){ return ((mint)1/2).pow(a); }

mint cal(ll N){
	if(N<=1)return 0;
	mint sum0=0;
	V<mint> dp(N+1);
	rep(a,1,N+1){
		mint f=0;
		f+=sum0*pw2(a);
		f+=pw2(a)-1;
		f-=a;
		f/=a;

		dp[a]=f;
		sum0+=f*pw2i(a);
	}
	return dp.back();
}

void tc()
{
	inl(N,K);
	vl A(K); in(A); each(a,A)--a;
	if(N==1)die(0);
	vl B(N,1); each(a,A)B[a]=0; // 自由か否か
	CumulativeSum cumB(B);

	ll border=0;
	V<tuple<ll,ll,ll>> nka;
	rep(i,K)if(border<=A[i]){
		ll n=N-border;
		ll k=n-cumB.query(border,N);
		ll a=A[i]-border;
		nka.eb(n,k,a);
		border=A[i]+1;
	}

	auto dfs=[&](auto&& self,ll u)->mint{
		if(u==nka.size())return cal(N-border);
		auto[n,k,a]=nka[u];
		mint ans=self(self,u+1);
		ans*=pw2(a+1);
		ans+=pw2(a)-1;
		return ans;
	};

	mint ans=dfs(dfs,0);
	out(ans*binom.fac(N-K));
}
void yamada::solve() { ini(T); while(T--)tc(); }
