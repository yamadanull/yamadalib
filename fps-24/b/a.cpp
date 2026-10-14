#include "../../template/template.hpp"
#include "../../fps/kitamasa.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N);
	fps nume0{1,1};
	fps nume1{1,1,1};
	fps deno0{1,0,-1};
	fps deno1{1,0,0,-1};
	out(LinearRecurrence(N,deno0*deno1,nume0*nume1));
}
