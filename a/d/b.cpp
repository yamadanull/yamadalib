#include "../../template/multitest-template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

vl table(ll N,ll K){
	auto idx=[&](ll k,ll u)->ll{return k*N+u;};
	UnweightedGraph g(N*K);
	rep(x,N)rep(k,K){
		{
			ll nx=x+(1LL<<k);
			ll nk=k+1;
			if(nx<N && nk<K)g[idx(k,x)].eb(idx(nk,nx));
		}
		if(x)g[idx(k,x)].eb(idx(0,x-1));
	}

	auto dp=bfs(g);
	/* rep(x,N)rep(k,K){ */
	/* 	err(x,k,dp[idx(k,x)]); */
	/* } */

	vl ans(N,infLL);
	rep(i,N)rep(k,K){
		ll d=dp[idx(k,i)];
		if(d>=0)amin(ans[i],d);
	}
	/* err(ans); */
	/* rep(i,1,N){ */
	/* 	err(i,ans[i],msb(i),lsb(i),msb(i)); */
	/* } */
	return ans;
}

const int LG=61;
ll f(ll X,ll C){
	ll ans=infLL;
	VVV(ll,dp,2,LG+1,LG+1,infLL); // popcntがiであり、X以上の最小の数
	dp[0][LG][0]=0;
	rep(p,2)repr(t,LG)rep(i,LG)if(dp[p][t+1][i]>=0){
		rep(d,2){
			if(!t&&d)continue;
			if(!p&&!d && X>>t&1)continue;
			ll P=p;
			if(d && !(X>>t&1))P=1;
			amin(dp[P][t][i+d],dp[p][t+1][i]+(1LL<<t)*d);
		}
	}
	return min(dp[0][0][C],dp[1][0][C]);
}

ll cal(ll x){
	ll ans=infLL;
	rep(c,1,LG){
		ll X=x+c*2-1;
		ll Y=f(X,c);
		ll bns=0;
		rep(t,LG)if(Y>>t&1)bns+=t;
		bns+=Y-x-c;
		amin(ans,bns);
	}
	return ans;
}

void exper(){
	IN(N,K);
	auto dp=table(N,K);
	rep(i,1,N)err(i,cal(i),dp[i]);
}

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	/* exper(); */
	IN(L,R); amax(L,1);
	mint ans=0;
	rep(i,L,R+1){
		ll bns=cal(i);
		err(i,bns);
		ans+=bns;
	}
	out(ans);
}
