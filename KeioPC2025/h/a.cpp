#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
constexpr int LG=30;
using namespace yamada;

ll digDP(ll W,ll D){ // Wの部分集合かつD以上となる最小の数
	vl dp(LG+1,infLL); // D以上が確定していない Wの部分集合
	vl ep(LG+1,infLL); // D以上が確定しています Wの部分集合
	dp[LG]=0;
	repr(t,LG){
		// 1にする
		if(W>>t&1){
			if(D>>t&1){
				amin(dp[t],dp[t+1]+(1LL<<t));
				amin(ep[t],ep[t+1]+(1LL<<t));
			}
			else{
				amin(ep[t],dp[t+1]+(1LL<<t));
				amin(ep[t],ep[t+1]+(1LL<<t));
			}
		}

		// 0にする
		if(D>>t&1){
			amin(ep[t],ep[t+1]);
		}
		else{
			amin(dp[t],dp[t+1]);
			amin(ep[t],ep[t+1]);
		}
	}
	return min(dp[0],ep[0]);
}

ll digDP_naive(ll W,ll D){
	rep(i,D,W+1)if((i|W)==W)return i;
	return infLL;
}

void digDP_check(){
	inl(W,D);
	assert(digDP(W,D)==digDP_naive(W,D));
}

vl cal(WeightedGraph<ll> g){
	ll N=g.size();
	minpq<pl> q;
	vl dist(N,infLL);
	dist[0]=1;
	q.emplace(1,0);
	while(!q.empty()){
		auto[d,u]=q.top(); q.pop();
		if(d!=dist[u])continue;
		each(e,g[u]){
			ll v=e.to;
			ll w=e.cost;
			if(amin(dist[v],digDP(w,d)))q.emplace(dist[v],v);
		}
	}

	return dist;
}

void yamada::solve()
{
	inl(N,M);
	auto g=wgraph<ll>(N,M);
	WeightedGraph<ll> h(N-1);
	rep(u,N-1)each(v,g[u])if(v<N-1)h[u].eb(v);

	auto dp=cal(g);
	auto ep=cal(h);
	ll ans=dp.back();
	if(ans==infLL)die(-1,-1);
	ll bns=ans;
	each(e,g[N-1]){
		ll u=e.to;
		ll w=e.cost;
		if(ep[u]<=w)amax(bns,w);
	}
	out(ans,bns);
}
