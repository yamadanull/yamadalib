#include "../../template/multitest-template.hpp"
#include "../../modulo/binomial.hpp"
#include "../../tree/tree-query.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
void yamada::solve()
{
	IN(N);
	vc<int> P(N); in(P|Drop(1)); each(p,P)--p;
	UnweightedGraph g(N);
	rep(i,1,N)g[P[i]].eb(i);
	Tree tree(g);

	min_segtree<ll> seg(vl(N,0)); // L
	seg.set(1,1);
	rep(u,2,N){
		ll l=tree.lca(u,u-1);
		if(l!=u-1){
			seg.set(u,seg(l+1,u));
		}
		else{
			seg.set(u,u);
		}
	}
	/* err(seg.get()); */
	mint ans=[&](this auto dfs,ll L,ll R)->mint{
		/* err(L,R); */
		if(L+1==R)return 1;
		ll r=R-1;
		mint ans=1;
		while(r!=L){
			ll l=seg[r-1];
			ans*=dfs(l,r);
			ans*=binom(R-1-l,r-l);
			r=l;
		}
		return ans;
	}(1,N+1);
	out(ans);
}
