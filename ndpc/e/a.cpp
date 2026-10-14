#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

constexpr int LG=20;
void yamada::solve()
{
	inl(N,M,Q);
	vp ab(M); in(ab); each2(a,b,ab)--a;

	sort(all(ab),[&](pl x,pl y){return x.se!=y.se? x.se<y.se: x.fi<y.fi;});
	vl A,B; each2(a,b,ab)A.eb(a),B.eb(b);
	AddMax_LazySegmentTree<ll,-infLL> seg(A);

	vv(ll,dp,LG,M+1,M);
	rep(u,M){
		auto[a,b]=ab[u];
		ll v=seg.max_right(u+1,[&](ll mx){return mx<b;});
		dp[0][u]=v;
	}
	rep(t,1,LG)rep(u,M)dp[t][u]=dp[t-1][dp[t-1][u]];

	B.eb(infLL);
	while(Q--){
		inl(L,R); --L;
		ll pos=seg.max_right(0,[&](ll mx){return mx<L;});
		if(B[pos]>R){
			out(0);
			continue;
		}
		ll ans=1;
		repr(t,LG){
			ll to=dp[t][pos];
			if(B[to]>R)continue;
			pos=to;
			ans+=1LL<<t;
		}
		out(ans);
	}
}
