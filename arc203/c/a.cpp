#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(H,W,K);
		if(K<H+W-2){ out(0); continue; }
		if(K==H+W-2){ out(binom(H+W-2,H-1)); continue; }

		ll wcnt=(H-1)*W+H*(W-1)-(H+W-2);
		if(K==H+W-1){
			out(binom(H+W-2,H-1)*wcnt);
			continue;
		}

		mint ans=binom(H+W-2,H-1);
		ans*=mint(wcnt)*(wcnt-1)/2;
		ans-=binom(H+W-4,H-2)*(H+W-3);
		rep(2){
			swap(H,W);
			ll a=H-2-1,b=W+1-1;
			if(a>=0 && b>=1){
				ans+=binom(vl{a,b,1});
				ans-=binom(vl{a,b+1})*2;
			}
		}
		out(ans);
	}
}
