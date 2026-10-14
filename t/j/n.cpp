#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
void tc()
{
	inl(A,B,K);
	i128 ans=-infLL;
	rep(k,K+1)rep(msk,1<<k){
		i128 bns=0;
		rep(i,k){
			if(msk>>i&1)bns*=B;
			else bns+=A;
		}
		amax(ans,bns);
	}
	out(ans%mint::get_mod());
}
void yamada::solve() { inl(T); while(T--)tc(); }
