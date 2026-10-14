#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N,M);
	vl A(N); in(A);
	vl cnt(N);
	rep(N){
		inl(a);
		cnt[a]++;
	}

	mint ans=1;
	rep(i,1,N,2){
		vl dnt;
		for(ll j=i; j<N; j*=2){
			dnt.eb(cnt[j]);
		}
		ans*=cal(dnt);
	}
	out(ans);
}
