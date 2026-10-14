#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(N);
	fps F(N+1);
	rep(k,1,N+1){
		inl(a);
		for(ll i=1; i*k*(a+1)<=N; i++){
			F[i*k*(a+1)]-=((mint)i).inverse();
		}
		for(ll i=1; i*k<=N; i++){
			F[i*k]+=((mint)i).inverse();
		}
	}
	out(F.exp()[N]);
}
