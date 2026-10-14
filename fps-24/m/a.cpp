#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N);
	fps F(N+1,1);
	rep(i,1,N+1){
		F[i]=((mint)2).pow(i*(i-1)/2)*binom.finv(i);
	}
	F=F.log();
	out(F[N]*binom.fac(N));
}
