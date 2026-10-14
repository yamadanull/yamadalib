#include "../../template/template.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-compress.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

lld E(ll cnt,ll dnt){ return lld(cnt+dnt)/cnt; }

lld cal(UnweightedGraph g,vl reds){
	ll N=g.size();
	if(reds.size()==1){
		lld ans=0;
		rep(u,N)if(u!=reds[0])ans+=E(1,g[u].size()-1);
		return ans;
	}

	ll root=-1;
	{
		Tree T(g);
		auto path=T.path(reds[0],reds[1]);
		assert(path.size()>=3);
		root=path[1];
	}

	V<bool> fn(N); // 先に塗るべきかどうか
	V<bool> gn(N); // 後に塗るべきかどうか
	{
		vl cnt(N),dnt(N);
		each(u,reds)++cnt[u];
		auto dfs=[&](auto&& self,ll u,ll p)->void{
			each(v,g[u])if(v!=p){
				self(self,v,u);
				if(cnt[v]>0)++cnt[u];
				else ++dnt[u];
			}
		}; dfs(dfs,root,-1);
		rep(u,N){
			if(cnt[u]>0){
				if(!binary_search(all(reds),u))fn[u]=1;
			}
			else gn[u]=1;
		}
	}
	vl cnt(N),dnt(N);
	rep(u,N)each(v,g[u]){
		if(fn[v] || binary_search(all(reds),v))++cnt[u];
		else ++dnt[u];
	}

	lld ans=infLL;
	{
		lld sum=0;
		rep(u,N)if(fn[u])sum+=E(cnt[u]-1,dnt[u]+1);
		rep(u,N)if(fn[u]){
			// uが最後に塗る頂点のとき
			auto bns=sum;
			bns-=E(cnt[u]-1,dnt[u]+1);
			bns+=E(cnt[u],dnt[u]);
			amin(ans,bns);
		}
	}

	rep(u,N)if(gn[u])ans+=E(1,g[u].size()-1);
	return ans;
}

void tc()
{
	inl(N);
	ins(S);
	auto g=graph(N);
	UnionFind uf(N);
	rep(u,N)each(v,g[u]){
		if(S[u]=='0' && S[v]=='0'){
			uf.unite(u,v);
		}
	}

	Tree T(g);
	lld ans=0;
	each(gr,uf.groups()){
		if(S[gr[0]]=='1')continue;
		auto xs=gr;
		each(u,gr){
			each(v,g[u])if(S[v]=='1')xs.eb(v);
		}

		ll n=xs.size();
		UnweightedGraph ng(n);
		compress cmp(xs);
		/* vl p(n,-1); */
		rep(u,n){
			ll U=cmp[u];
			ll v=cmp(T.par(U));
			if(v<0)continue;
			ng[u].eb(v);
			ng[v].eb(u);
		}

		vl reds;
		rep(u,n)if(S[cmp[u]]=='1')reds.eb(u);
		ans+=cal(ng,reds);
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
