#include "../../template/template.hpp"
#include "../../modulo/multipoint-binomial-sum.hpp"
#include "../../graph/graph-template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
vc<mint> get_tab_naive(ll N){
	vc<mint> ans(N);
	rep(s,1,N){
		rep(j,N-s+1){
			ans[s]+=binom(N-s,j)*j;
		}
		ans[s]*=mint(2).pow(s);
	}
	rep(s,1,N){
		rep(k,N-s+1){
			ans[s]-=binom(N,s+k)*k;
		}
	}
	return ans;
}
vc<mint> get_tab(ll N){
	vc<mint> ans(N);
	{
		vector<pair<int,int>> qs;
		rep(i,N)qs.eb(i,i+1);
		auto A=multipoint_binomial_sum2(qs,binom).se;
		err(A);
		rep(s,1,N){
			ans[s]+=A[N-s];
			ans[s]*=mint(2).pow(s);
		}
	}
	{
		vc<mint> A0(N+1),A1(N+1);
		rep(i,N+1){
			A0[i]=binom(N,i);
			A1[i]=binom(N,i)*i;
		}
		CumulativeSum cum0(A0),cum1(A1);
		rep(s,1,N){
			ans[s]-=cum1(s,N+1);
			ans[s]+=cum0(s,N+1)*s;
		}
	}
	return ans;
}

void yamada::solve()
{
	inl(N);
	auto g=graph(N);
	vl dp(N,1);
	auto dfs=[&](auto&& self,ll u,ll p)->void{
		each(v,g[u])if(v!=p){
			self(self,v,u);
			dp[u]+=dp[v];
		}
	};
	dfs(dfs,0,-1);

	auto tab=get_tab(N);
	mint ans=0;
	rep(u,1,N){
		ans+=tab[dp[u]];
	}
	out(ans);
}
