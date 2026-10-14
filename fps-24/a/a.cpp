#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(D,N);
	fps F={0,1,0,1,1,0,1};
	F=F.pow(D,1<<20);
	out(F[N]);
}
