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
	fps F(M+1);
	rep(i,1,M+1,2)F[i]=1;
	// Bの末尾ー先頭
	F=F.pow(N-1);

	mint ans=0;
	rep(i,M+1){
		mint bns=F[i];
		bns*=M-i+1;
		ans+=bns;
	}
	ans*=binom.fac(N);
	out(ans);
}
