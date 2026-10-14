#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,M);
	fps ans{1};
	rep(i,1,M+1){
		fps F(i+1,1);
		rep(i,F.size())F[i]*=binom.finv(i);
		ans*=F;
		ans=ans.pre(N+1);
	}
	out(ans[N]*binom.fac(N));
}
