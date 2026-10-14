#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../ntt/relaxed-convolution.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N);

	// マスiにいた事のある確率
	fps F(N+1);
	rep(i,N+1)F[i]=binom.fac(i);

	// 初違反がiである通り数（そこからの数は無視）
	fps G(N+1);
	// 今までに違反をしてなおかつiで違反する通り数（そこからの数は無視）
	RelaxedConvolution<fps> rc(N+1);
	rc.get(0,0);
	rep(i,1,N+1){
		G[i]=binom.fac(i);
		G[i]-=rc.c[i];
		rc.get(F[i],G[i]);
	}

	mint ans=binom.fac(N);
	rep(i,1,N){
		ans-=G[i]*binom.fac(N-i);
	}
	out(ans);
}
