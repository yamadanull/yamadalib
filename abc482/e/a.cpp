#include "../../template/template.hpp"
#include "../../graph/graph-utility.hpp"
#include "../../tree/tree-query.hpp"
#include "../../tree/auxiliary-tree.hpp"
#include "../../tree/rerooting.hpp"
using namespace yamada;

//[直径、個数]
pl cal_dp(Tree<UnweightedGraph>& tree,UnweightedGraph g,vint cmp,vl fn){
	ll N=len(g);
	using T = pl; // 直径、個数
	T leaf = {0,0};
	// T 同士をマージ
	auto f1 = [&](T x, T y) -> T {
		if(x.fi==y.fi)return{x.fi,x.se+y.se};
		return max(x,y);
	};
	// T の根に頂点 c および辺 c-p を追加する (p は virtual)
	auto f2 = [&](T x, int c, int p) -> T {
		ll d=tree.len(cmp[c],cmp[p]);
		if(x.se>0){
			x.fi+=d;
			return x;
		}
		if(fn[c]){
			return{d,1};
		}
		return x;
	};
	Rerooting<T, decltype(g), decltype(f1), decltype(f2)> dp(g, f1, f2, leaf);
	T ans{-1,-1};
	rep(u,N)if(fn[u]){
		/* if(N==6)err(u,dp[u]); */
		if(ans.fi<dp[u].fi)ans=dp[u];
		else if(ans.fi==dp[u].fi)ans.se+=dp[u].se;
	}
	return ans;
}

void yamada::solve()
{
	IN(N);
	auto g=graph(N);
	Tree tree(g);
	vvc<int> Us(N);
	rep(u,N){
		IN(c); --c;
		Us[c].eb(u);
	}
	ll DIA=Diameter(g).se;

	AuxiliaryTree at(g);
	ll ans=0;
	each(us,Us)if(!us.empty()){
		auto[h,cmp]=at.get(us);
		ll n=len(h);
		vl fn(n);
		each(ci,u,cmp|Enumerate)if(BinarySearch(us,u))fn[ci]=1;
		auto[d,c]=cal_dp(tree,h,cmp,fn);
		/* err(h,us,cmp,d,c); */
		if(d==DIA)ans+=c;
	}
	err(ans);
	out(ans/2);
}
