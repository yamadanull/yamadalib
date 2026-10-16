#include "../../template/multitest-template.hpp"
#include "../../graph/graph-template.hpp"
#include "../../data-structure/union-find.hpp"

void yamada::solve()
{
	IN(N,M);
	vp es;
	UnionFind uf(N);
	UnweightedGraph g(N);
	rep(M){
		IN(u=--LL,v=--LL);
		if(uf.unite(u,v)){
			g[u].eb(v);
			g[v].eb(u);
		}
		else es.eb(u,v);
	}
	auto grs=uf.groups();
	each(gr,grs)if(len(gr)==1)DIE("Brain Melt");
	if(len(grs)>=2)DIE("Many");
	if(!es.empty())DIE("Many");

	vl cnt(N);
	rep(u,N)cnt[len(g[u])]++;
	err(cnt);
	out(cnt[1]==N-1? "2":"Many");
}
