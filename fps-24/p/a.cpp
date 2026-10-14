#include "../../template/template.hpp"
#include "../../fps/multipoint-evaluation.hpp"
#include "../../modulo/binomial.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,M,K);
	fps F(N+1);
	rep(k,K+1){
		F[N-k]=binom(N,k);
	}
	V<mint> xs(M+1);
	rep(i,M+1)xs[i]=i;
	auto ys=MultipointEvaluation(F,xs);
	rep(i,1,M+1)out(ys[i]);
}
