#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
mint f(ll n,ll m){
	mint ans=0;
	rep(i,n+1)rep(j,m+1){
		ans+=binom(n,i)*binom(m,j)*min(i,j);
	}
	return ans;
}

vc<mint> get_tab(ll N){
	/* vv(mint,A,N,N); */
	/* rep(i,1,N)rep(j,1,N){ */
	/* 	A[i][j]=f(i,j); */
	/* } */
	/* rep(i,1,10){ */
	/* 	auto b=BerlekampMassey(A[i]); */
	/* 	err(i,b); */
	/* } */
	/* rep(i,1,N)rep(j,1,N){ */
	/* 	if(i-j>=0)B[i][j]=A[i-j][j]; */
	/* 	else B[i][j]=0; */
	/* } */
	/* each(a,A)err(a); */
	/* each(b,B){ */
	/* 	while(!b.empty() && b.back()==0)b.pop_back(); */
	/* 	err(b); */
	/* } */
	vc<mint> ans(N+1);
	rep(i,1,N)ans[i]=f(N-i,i);
	return ans;
}

void yamada::solve()
{
	inl(N);
	auto g=graph(N);
	auto B=get_tab(N);
	vl dp(N,1);
	auto dfs=[&](auto&& self,ll u,ll p)->void{
		each(v,g[u])if(v!=p){
			self(self,v,u);
			dp[u]+=dp[v];
		}
	};
	dfs(dfs,0,-1);

	mint ans=0;
	rep(u,N){
		ans+=B[dp[u]];
	}
	out(ans);
}
