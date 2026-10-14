#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N,M);
	fps nume{1,-1};
	fps deno{1,-2};
	deno=deno.pow(N+1,M+1);
	out((nume*deno.inv())[M]);
}
