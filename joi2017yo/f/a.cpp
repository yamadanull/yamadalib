#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"

void yamada::solve()
{
	ini(N,M,K);
	// st: 0:cold 1:hot 2:comfortable
	// k minute
	auto idx=[&](int st,int k,int u){return N*K*st+N*k+u;};
	V<int> A(N); in(A);
	each(t,A){
		if(t==1)t=2;
		else if(t==2)t=1;
	}

	auto g=wgraph<int>(N,M);
	// dist,state,time,u
	minpq<tuple<int,int,int,int>> q;
	q.emplace(0,0,0,0);
	vvv(int,dp,3,K,N,inf);
	dp[0][0][0]=0;

	while(!q.empty()){
		auto[d,st,t,u]=q.top(); q.pop();
		if(dp[st][t][u]!=d)continue;
		/* out(d,st,t,u); */

		each(v,g[u]){
			/* out(u,v); */
			auto update=[&](int nst,int nt){
				if(amin(dp[nst][nt][v],d+v.cost)){
					q.emplace(d+v.cost,nst,nt,v);
				}
			};

			if(st<=1 && t+v.cost<K){
				if(A[v]==1-st)continue;
				else if(A[v]==2)update(st,t+v.cost);
				else update(A[v],0);
			}
			else{
				update(A[v],0);
			}
		}
	}

	int ans=inf;
	rep(st,3)rep(k,K)amin(ans,dp[st][k][N-1]);
	out(ans);
}
