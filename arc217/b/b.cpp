#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
mint pw2(ll a){ return ((mint)2).pow(a); }
mint pw2i(ll a){ return ((mint)1/2).pow(a); }

mint cal(ll N){
	if(N==0)return 0;
	mint sum0=0;
	V<mint> dp(N+1);
	rep(i,1,N+1){
		mint f=0;
		f+=sum0*pw2(i);
		f+=binom.fac(i-1)*(pw2(i)-1);
		f-=binom.fac(i-1)*i;

		dp[i]=f;
		sum0+=f*pw2i(i);
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

	mint ans=cal(N-border);
	reverse(all(nka));
	each3(n,k,a,nka){
		ans*=pw2(a+1);
		ans+=(pw2(a)-1)*binom.fac(n-k);
	}

	/* out(cof,ans); */
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
