#include "../../template/template.hpp"
#include "../../data-structure/slope-trick.hpp"
#include "../../graph/namori.hpp"
#include "../../graph/undirected-namori.hpp"
using namespace yamada;

ll treeDP(WeightedGraph<ll> g,vl A){
	ll N=g.size();
	auto dfs=[&](auto&& self,ll u)->void{
		each(v,g[u]){
			self(self,v);
			A[u]+=A[v];
		}
	}; dfs(dfs,0);
	/* out(A); */
	ll ans=0;
	rep(i,1,N)ans+=abs(A[i]);
	return ans;
}

ll cycDP(vl A){
	ll N=A.size();
	A=mkrui(A);
	SlopeTrick st;
	rep(i,N){
		st.add_abs_xma(A[i]);
	}
	return st.get_min().se;
}

void yamada::solve()
{
	inl(N);
	auto g=graph(N,N);
	g=UndirectedNamori(g);
	Namori<ll> nam(N);
	rep(i,N)nam.add_edge(i,g[i][0]);

	vl A(N); in(A);
	rep(i,N){
		inl(b);
		A[i]-=b;
	}

	ll K=nam.aux.size();
	vvl memo(K);
	rep(ci,K)memo[ci].resize(nam.aux[ci].size());
	rep(i,N){
		auto[a,b]=nam.idx(i);
		memo[a][b]=i;
	}

	ll ans=0;
	vl C(K);
	rep(ci,K){
		auto aux=nam.aux[ci];
		ll n=aux.size();
		vl B(n);
		rep(i,n)B[i]=A[memo[ci][i]];
		ans+=treeDP(aux,B);
		C[ci]=Sum(B);
		/* out(ans); */
	}
	ans+=cycDP(C);
	out(ans);
}
