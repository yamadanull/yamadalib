#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(N,A=LL*N);
	mint ans=0;
	rep(l,N)rep(r,l+1,N+1){
		ll x=Max(A|Take(r)|Drop(l));
		ll y=Min(A|Take(r)|Drop(l));
		ans+=(x-y)*(x-y);
	}
	out(ans);
}
