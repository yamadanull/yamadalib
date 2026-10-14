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
	fps F(N+1);
	rep(i,3,N+1){
		F[i]=((mint)i).inverse();
	}

	F=F.exp();
	out(F[N]*binom.fac(N));
}
