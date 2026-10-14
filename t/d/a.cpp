#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../graph/graph-compress.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
mint cal(UnweightedGraph g){
	ll N=g.size();
	auto dp=bfs(g);
	rep(u,N)each(v,g[u]){
		if(dp[u]%2==dp[v]%2)return 0;
	}

	vl cnt(2);
	rep(i,N)cnt[dp[i]%2]++;
	mint ans=0;
	each(c,cnt){
		ans+=((mint)2).pow(c);
	}
	return ans;
}

void tc()
{
	inl(N,M);
	auto g=graph(N,M);
	auto subs=ConnectedComponents(g);
	mint ans=1;
	each(sub,subs){
		ans*=cal(sub.g);
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
