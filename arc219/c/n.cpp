#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(H,W,N);
	auto idx=[&](ll i,ll j)->ll{return i*W+j;};
	WeightedGraph<ll> g(H*W);
	rep(i,H)rep(j,W){
		/* out(i,j); cout.flush(); */
		if(j==0 || j==W-1){
			if(i<H-1)g[idx(i,j)].eb(idx(i+1,j),0);
			if(i>0)g[idx(i,j)].eb(idx(i-1,j),0);
		}
		if(j>0)g[idx(i,j)].eb(idx(i,j-1),1);
		if(j<W-1)g[idx(i,j)].eb(idx(i,j+1),1);
	}

	vvl dist;
	rep(i,H)rep(j,W)dist.eb(dijkstra(g,idx(i,j)));

	vl ps;
	rep(N){
		inl(a,b); --a; --b;
		ps.eb(idx(a,b));
	}

	vv(ll,dp,1<<N,N,infLL);
	vv(pl,ep,1<<N,N,mkp(-1,-1));
	rep(i,N)dp[1<<i][i]=dist[0][ps[i]];
	rep(msk,1<<N)rep(i,N)if(dp[msk][i]<infLL){
		rep(j,N)if(!(msk>>j&1)){
			ll nsk=msk|(1<<j);
			ll add=dist[ps[i]][ps[j]];
			if(amin(dp[nsk][j],dp[msk][i]+add)){
				ep[nsk][j]=mkp(msk,i);
			}
		}
	}

	ll ans=infLL;
	rep(i,N)amin(ans,dp.back()[i]+dist[0][ps[i]]);
	out(ans);

	/* pl pos=mkp(-1,-1); */
	/* rep(i,N)if(ans==dp.back()[i]+dist[0][ps[i]])pos=mkp((ll)dp.size()-1,i); */
	
	/* vp bns; */
	/* while(pos.fi>=0){ */
	/* 	ll u=ps[pos.se]; */
	/* 	bns.eb(u/W,u%W); */
	/* 	pos=ep[pos.fi][pos.se]; */
	/* } */
	/* each(b,bns)out(b); */
}
