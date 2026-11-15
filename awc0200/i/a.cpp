#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	IN(N,M,K,G,S,T,BIND(P,Q)=~PR(LL,LL)[N]); ++K;
	auto idx=[&](ll h,ll u){return h*N+u;};
	WeightedGraph<ll> g(N*K);
	rep(M){
		IN(u,v,L,R,C,H,D); ++R; --u; --v;
		rep(h,L,R){
			ll w=C+D*abs(h-H);
			g[idx(h,u)].eb(idx(h,v),w);
		}
	}
	rep(u,N){
		rep(h,K-1)g[idx(h,u)].eb(idx(h+1,u),P[u]);
		rep(h,1,K)g[idx(h,u)].eb(idx(h-1,u),Q[u]);
	}

	ll ans=infLL;
	rep(X,K)rep(Y,X+1,K+1)[&]{
		if(!inLR(X,S,Y))return;
		if(!inLR(X,T,Y))return;
		ll U=idx(S,0);
		ll V=idx(T,N-1);

		minpq<pl> q;
		q.emplace(0,U);
		vl dp(N*K,infLL);
		dp[U]=0;

		while(!q.empty()){
			auto[d,u]=q.top(); q.pop();
			/* if(N==3)err(X,Y,d,u); */
			if(dp[u]!=d)continue;
			each(v,g[u]){
				if(inLR(X,v/N,Y)){
					if(amin(dp[v],d+v.cost)){
						q.emplace(dp[v],v);
					}
				}
			}
		}
		/* err(U,V,dp); */
		ll bns=dp[V]+G*(Y-X-1);
		amin(ans,bns);
	}();
	if(ans<infLL)out(ans);
	else out("NA");
}
