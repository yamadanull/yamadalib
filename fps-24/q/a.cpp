#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,M,K);
	vl A(N),B(M); in(A,B);

	fps F,G;
	rep(2){
		swap(N,M); swap(A,B); swap(F,G);
		auto dfs=[&](auto&& self,ll l,ll r)->fps{
			if(r-l==1)return{1,-A[l]};
			ll m=(l+r)/2;
			return self(self,l,m)*self(self,m,r);
		};
		F=-dfs(dfs,0,N).log(K+2);
		rep(i,F.size())F[i]*=i;
		F[0]=N;
		/* F=dfs(dfs,0,N); */
	}
	/* out("F:",F); */
	/* out("G:",G); */
	rep(i,F.size())F[i]*=binom.finv(i);
	rep(i,G.size())G[i]*=binom.finv(i);
	auto H=F*G;
	rep(i,1,K+1){
		mint ans=H[i]*binom.fac(i);
		ans/=N*M;
		out(ans);
	}
}
