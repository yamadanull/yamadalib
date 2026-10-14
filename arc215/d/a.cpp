#include "../../template/template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<1000000007>;
Binomial<mint> binom;
void yamada::solve()
{
	auto cho=[](ll N,ll M)->mint{
		return binom(N+M-1,M-1);
	};
	auto mul_1_x=[](V<mint> F)->V<mint>{
		auto G=F;
		rep(i,1,F.size())F[i]-=G[i-1];
		return F;
	};

	/* auto div_1px=[](V<mint> F)->V<mint>{ */
	/* 	ll N=F.size(); */
	/* 	V<mint> ans(N); */
	/* 	rep(i,1,N,2)F[i]*=-1; */
	/* 	CumulativeSum cum(F); */
	/* 	rep(i,N){ */
	/* 		ans[i]=cum.prod(0,i+1); */
	/* 		if(i%2)ans[i]*=-1; */
	/* 	} */
	/* 	return ans; */
	/* }; */

	inl(N,M); ++N; ++M;

	ll n0=(N+1)/2;
	ll n1=N/2;
	V<mint>F(M+1),G(M+1);
	rep(i,1,M+1){
		F[i]=cho(n0,i);
		G[i]=cho(n1,i);
	}
	/* out(F); */
	/* out(G); */
	F=mul_1_x(mul_1_x(F));
	G=mul_1_x(mul_1_x(G));
	/* F=div_1px(mul_1_x(F)); */
	/* G=div_1px(mul_1_x(G)); */
	/* out(F); */
	/* out(G); */

	mint sumF=0,sumG=0;
	rep(i,M+1){
		sumF+=F[i];
		sumG+=G[i];
	}

	mint ans=0;
	ans+=sumF*sumG*(M*2+1);
	rep(i,M+1){
		ans-=F[i]*i*sumG;
		ans-=G[i]*i*sumF;
	}
	out(ans);
}
