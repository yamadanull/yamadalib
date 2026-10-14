#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	inl(N,K);
	vl A(N); in(A);
	if(Sum(A)<K)die(1);
	/* sort(all(A)); reverse(all(A)); */

	auto B=mkrui(A);
	ll sum=Sum(A);
	ll cnt=0;
	rep(i,N){
		if(sum-A[i]<K)++cnt;
	}

	mint ans=binom.fac(N);
	if(cnt>=3){
		ans/=binom.fac(cnt-1);
		out(ans);
	}
	else out(ans);

	/* ll R=lb(B,K); */
	/* if(R==1)die(binom.fac(N)); */

	/* rep(i,R){ */
	/* 	ll a=A[i]; */
	/* 	ll b=A[(i+1)%R]; */
	/* 	if(sum-a-b>=K) */
	/* } */
}
