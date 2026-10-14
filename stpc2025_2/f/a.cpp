#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N);
	ins(S); reverse(all(S));
	if(N==1)die(S);
	// 10^2^i
	V<mint> pw(N+1);
	pw[0]=10;
	rep(i,1,pw.size())pw[i]=pw[i-1]*pw[i-1];
	V<fps> F(N-1);
	rep(i,N-1)F[i]={1,pw[i]};
	
	auto dfs=[&](auto&& self,ll L,ll R)->fps{
		if(R-L==1)return F[L];
		ll M=(L+R)/2;
		return self(self,L,M)*self(self,M,R);
	};

	auto A=dfs(dfs,0,N-1);
	mint ans=0;
	rep(i,N){
		ans+=A[i]*(S[i]-'0');
	}
	out(ans);
}
