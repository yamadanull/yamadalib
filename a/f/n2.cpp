#include "../../template/template.hpp"
#include "../../graph/strongly-connected-components.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-template.hpp"
 
void yamada::solve()
{
	inl(N,K);
	UnweightedGraph g(N);
	rep(i,1,N){
		inl(p); --p;
		g[p].eb(i);
	}

	UnweightedGraph h(N);

	Tree tree(g);
	rep(u,N)if(g[u].empty()){
		ll v=tree.par(u);
		ll dist=1;
		while(v>=0){
			h[v].eb(u);
			if(dist<=K)h[u].eb(v);
			++dist;
			v=tree.par(v);
		}
	}

	auto idx=[&](ll msk,ll u){return msk*N+u;};
	UnweightedGraph f(Power(2,N)*N);
	rep(msk,1<<N)rep(u,N){
		each(v,h[u]){
			ll nsk=msk|1<<v;
			f[idx(msk,u)].eb(idx(nsk,v));
		}
	}

	StronglyConnectedComponents scc(f);
	auto dag=scc.dag;
	ll D=dag.size();
	vl dp(D,-infLL);
	dp[scc[idx(1,0)]]=0;
	rep(u,D)if(dp[u]>=0){
		ll u_ori=scc.belong(u)[0];
		ll msk=u_ori/N;
		each(v,dag[u]){
			ll v_ori=scc.belong(v)[0];
			ll nsk=v_ori/N;

			ll add=0;
			if(msk!=nsk){
				ll u_g=ctz(msk^nsk);
				if(g[u_g].empty())add++;
			}
			amax(dp[v],dp[u]+add);
		}
	}
	out(Max(dp));
}
