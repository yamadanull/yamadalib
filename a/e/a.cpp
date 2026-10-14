#include "../../template/template.hpp"
#include "../../tree/rerooting.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	IN(N);
	auto g=graph(N);
	// 「T : 根が virtual である根付き木」に対応する情報を管理する
	using T = pl;
	// 空の状態に対応する情報
	T leaf = {0,0};
	// T 同士をマージ
	auto f1 = [&](T x, T y) -> T {
		x.fi+=y.fi;
		x.se+=y.se;
		return x;
	};
	// T の根に頂点 c および辺 c-p を追加する (p は virtual)
	auto f2 = [&](T x, int c, int p) -> T {
		x.fi+=++x.se;
		return x;
	};
	Rerooting<T, decltype(g), decltype(f1), decltype(f2)> dp(g, f1, f2, leaf);
	ll ans=0;
	rep(i,N)amax(ans,dp[i].fi+N);
	out(ans);
}
