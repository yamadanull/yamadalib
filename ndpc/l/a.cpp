#include "../../template/template.hpp"
#include "../../multiplicative-function/divisor-multiple-transform.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N);
	VV<int> dss(N+1);
	rep(d,1,N+1){
		rep(i,d,N+1,d){
			dss[i].eb(d);
		}
	}

	V<mint> dp(N+1); // aがiの倍数での「通り数*a」合計
	rep(q,N){
		inl(a);
		auto ds=dss[a];
		ll n=ds.size();

		V<mint> ep(n);
		rep(i,n)ep[i]=dp[ds[i]];
		auto pc=factor_count(a);
		each2(p,cnt,pc){
			rep(di,n){
				ll dI=lb(ds,ds[di]*(int)p);
				if(dI>=n || ds[dI]!=ds[di]*p)continue;
				ep[di]-=ep[dI];
			}
		}

		mint ans=0;
		rep(i,n){
			ll d=ds[i];
			ans+=ep[i]/d;
		}

		/* map<ll,mint> ep; */
		/* each(d,ds)ep[d]=dp[d]; */
		/* multiple_transform::mobius_transform(ep); */
		/* mint ans=0; */
		/* each2(d,c,ep)ans+=c/d; */

		ans*=a;
		if(q>0)out(ans);
		else ans=1;

		each(d,ds){
			dp[d]+=ans*a;
		}
	}
}
