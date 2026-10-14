#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../graph/strongly-connected-components.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
void tc()
{
	inl(N,M);
	auto g=graph(N,M,1);
	StronglyConnectedComponents scc(g);
	g=scc.dag;

	ll st=scc[0];
	ll go=scc[N-1];
	V<mint> dp(N);
	dp[st]=1;
	rep(u,N)each(v,g[u])dp[v]+=dp[u];
	out(dp[go]);
}
void yamada::solve() { ini(T); while(T--)tc(); }
