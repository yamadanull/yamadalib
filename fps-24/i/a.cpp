#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N,K);
	V<fps> F(N);
	rep(i,N){
		inl(a);
		F[i]={1,a};
	}

	auto dfs=[&](auto&& self,ll L,ll R)->fps{
		if(R-L==1)return F[L];
		ll M=(L+R)/2;
		return self(self,L,M)*self(self,M,R);
	};

	out(dfs(dfs,0,N)[K]);
}
