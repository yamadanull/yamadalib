#include "../../template/multitest-template.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

ll caldp(UnweightedGraph g){ // 使われない頂点を返す
	ll N=len(g);
	if(N==1)return -1;
	auto[ans,bns]=[&](this auto dfs,ll u,ll p)->pl{
		ll ans=1,bns=0; // 使う、使わない
		each(v,g[u])if(v!=p){
			auto[ans0,bns0]=dfs(v,u);
			ans+=bns0;
			bns+=max(ans0,bns0);
		}
		return{ans,bns};
	}(0,-1);
	return ans>bns? g[0][0]:0;
}

void yamada::solve()
{
	IN(K);
	vl U(K);
	each(u,U){
		u=caldp(graph(INT()));
	}

	ll ti=-1;
	rep(k,K)if(U[k]>=0)ti=k;

	if(ti<0){
		rep(k,K-1){
			out(k+1,1,K,1);
		}
	}
	else{
		rep(k,K)if(k!=ti){
			out(ti+1,U[ti]+1,k+1,1);
		}
	}
}
