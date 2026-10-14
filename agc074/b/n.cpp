#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	UnweightedGraph g(1<<N);
	rep(S,1<<N){
		auto dig=Digit(S,2LL,N);
		CumulativeSum cum(dig);
		rep(l,N)rep(r,l+1,N)rep(L,r,N){
			ll R=L+r-l;
			if(R>N)continue;
			if(cum.query(l,r)!=cum.query(L,R))continue;
			auto ndig=dig;
			rep(i,l,r){
				ll j=L+i-l;
				swap(ndig[i],ndig[j]);
			}

			ll T=0;
			rep(i,N)if(ndig[i])T+=1<<i;
			g[S].eb(T);
		}
	}
	rep(u,1<<N){
		vector<int> es;
		each(v,g[u])if(v!=u)es.eb(v);
		g[u]=mkuni(es);
	}

	ll st=0,go=0;
	rep(i,N)if(A[i])st+=1<<i;
	rep(i,N)if(B[i])go+=1<<i;

	vl cur;
	auto dfs=[&](auto&& self,ll u)->void{
		cur.eb(u);
		if(u==go){
			out();
			each(v,cur)out(Digit(v,2LL,N));
			cur.pop_back();
			return;
		}
		if(cur.size()<4)each(v,g[u])self(self,v);
		cur.pop_back();
	};
	dfs(dfs,st);

	/* auto d=bfs(g,st); */

	/* vvl pre(1<<N); */
	/* rep(u,1<<N)if(d[u]>0){ */
	/* 	each(v,g[u]){ */
	/* 		if(d[v]==d[u]-1)pre[u].eb(v); */
	/* 	} */
	/* } */

	/* rep(u,1<<N)if(!pre[u].empty()){ */
	/* 	pre[u]=mkuni(pre[u]); */
	/* 	out(Digit(u,2LL,N),":"); */
	/* 	each(v,pre[u])out(Digit(v,2LL,N)); */
	/* } */
}
