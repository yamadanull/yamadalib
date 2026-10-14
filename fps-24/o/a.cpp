#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../prime/prime-enumerate.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N);
	fps P(N+1);
	P[0]=1;
	{
		auto ps=prime_enumerate(N+1);
		each(p,ps)if(p<=N)P[p]=binom.finv(p);
	}

	mint ans=P.pow(N)[N-1];
	ans/=N;
	ans/=N;
	ans*=binom.fac(N);
	out(ans);
}
