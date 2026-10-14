#include "../../template/template.hpp"
#include "../../modulo/multipoint-binomial-sum.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../geometry/line.hpp"

using mint = LazyMontgomeryModInt<1000000007>;
void yamada::solve()
{
	inl(op);
	if(op==0){
		out(5);
	}
	else if(op==1){
		out(5);
	}
	else if(op==2){
		ll L=0,R=1e4;
		ll ans=0;

		ans+=(R-L)*(R-L)*(R-L);
		ans-=1;
		out(ans);
	}
	else if(op==3){
		ll M=5e15; ++M;
		ll m1=bisect<ll>(0,inf,[&](ll x){return x*x*2<M;});
		ll m2=bisect<ll>(0,inf,[&](ll x){return x*x+(x+1)*(x+1)<M;});
		out(m1-1+m2);
	}
	else if(op==4){
		/* Line dp(Point(0,5),Point(sqrt(15),0)); */
		/* auto Q=projection(dp,Point(0,0)); */
		/* Point C(sqrt(15),4); */
		out(1);
	}
	else{
		/* ll N=2e6; */
		/* vector<pair<int,int>> qs; */
		/* V<bool>fn; */
		/* rep(ij,N*2+1){ */
		/* 	ll imax=min(N,ij); */
		/* 	ll imin=max(0LL,ij-N); */
		/* 	qs.eb(ij,imax); */
		/* 	fn.eb(1); */
		/* 	if(imin>0){ */
		/* 		qs.eb(ij,imin-1); */
		/* 		fn.eb(0); */
		/* 	} */
		/* } */

		/* auto res=multipoint_binomial_sum<mint>(qs); */
		/* mint ans=0; */
		/* rep(i,res.size()){ */
		/* 	if(fn[i])ans+=res[i]; */
		/* 	else ans-=res[i]; */
		/* } */
		/* out(ans); */
		out(208569179);
	}
}
