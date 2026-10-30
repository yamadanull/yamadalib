#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void yamada::solve()
{
	IN(N,P1,Q1,P2,Q2,XY=PR(LL,LL)*N,AB=PR(LL,LL)*N);
	ll M=1001;
	auto idx=[&](ll i,ll j)->ll{return i*M+j;};
	UnweightedGraph g(M*M);
	rep(x,M)rep(y,M){
		ll a=x*P1/Q1;
		ll b=y*P2/Q2;
		if(a<M&&b<M)g[idx(x,y)].eb(idx(a,b));
		if(x<M-1)g[idx(x,y)].eb(idx(x+1,y));
	}
	VV(ll,dist,N,N);
	rep(i,N){
		auto[x,y]=XY[i];
		auto dp=bfs(g,idx(x,y));
		rep(j,N){
			auto[a,b]=AB[j];
			ll d=dp[idx(a,b)];
			dist[i][j]=d<0?infLL:(ll)d;
		}
	}

	ll ans=infLL;
	nxp(N,[&](auto P){
		ll bns=0;
		rep(i,N){
			bns+=dist[i][P[i]];
			if(bns>=infLL)break;
		}
		amin(ans,bns);
	});
	out(ans==infLL? -1:ans);
}
