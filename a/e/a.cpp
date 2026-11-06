#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
const int M=6000;
void yamada::solve()
{
	fps F=(fps{1,0,-1,-1}).inv(M);
	fps G=((fps{0,1}).exp(M)-1).exp(M);
	rep(i,M)G[i]*=binom.fac(i);

	IN(T);
	while(T--){
		IN(N,S=STR);
		each(c,S)c-='0';
		auto T=S;
		T[0]=0;
		rep(i,1,N)T[i]=S[i]^S[i-1];

		vl fn(N);
		mint bns=1;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && T[l]==T[r])++r;
			if(!T[l])continue;
			rep(i,l-1,r)fn[i]=1;
			bns*=F[r-l+1];
		}

		ll ans=N*2;
		vl cnt(2);
		rep(i,N)if(!fn[i]){
			cnt[S[i]]++;
			ans--;
		}
		each(c,cnt)bns*=G[c];

		out(ans,bns);
	}
}
