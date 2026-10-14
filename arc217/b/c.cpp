#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
mint pw2(ll a){ return ((mint)2).pow(a); }
mint pw2i(ll a){ return ((mint)1/2).pow(a); }

mint cal(ll N){
	if(N<=1)return 0;

	mint ans=0;
	rep(a,N){
		// A[0]=a
		mint bns=cal(N-a-1);
		bns*=binom.fac(N-1)/binom.fac(N-a-1);
		bns*=pw2(a+1);
		bns+=(pw2(a)-1)*binom.fac(N-1);
		ans+=bns;
	}
	return ans;
}

mint cal(ll N,vl A){
	ll K=A.size();
	if(K==0){
		mint ans=cal(N);
		/* out(N,ans); */
		return ans;
	}

	vl B;
	ll M=A[0]+1;
	rep(i,1,K)if(A[i]>=M)B.eb(A[i]-M);
	mint ans=cal(N-M,B);
	ans*=binom.fac(N-K)/binom.fac(N-M-B.size());
	ans*=pw2(M);
	ans+=(pw2(M-1)-1)*binom.fac(N-K);
	return ans;
}

void tc()
{
	inl(N,K);
	vl A(K); in(A); each(a,A)--a;
	mint ans=cal(N,A);
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
