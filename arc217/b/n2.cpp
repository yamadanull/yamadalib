#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
mint pw2(ll a){ return ((mint)2).pow(a); }
mint pw2i(ll a){ return ((mint)1/2).pow(a); }

ll cal(vl A){
	ll N=A.size();
	if(N<=1)return 0;
	vl B;
	ll M=A[0]+1;
	rep(i,N)if(A[i]>A[0])B.eb(A[i]-M);

	ll ans=cal(B);
	ans*=1<<(M);
	ans+=MSK(M-1);
	return ans;
}

void tc()
{
	inl(N,K);
	vl A(K); in(A); each(a,A)--a;
	vl B(N); rep(i,N)B[i]=i;
	mint ans=0;
	do{
		bool fn=1;
		rep(i,K)if(A[i]!=B[i]){
			fn=0;
			break;
		}

		if(fn)ans+=cal(B);
	}while(nxp(B));
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
