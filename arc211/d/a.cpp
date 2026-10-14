#include "../../template/template.hpp"
#include "../../shortest-path/bfs-restore.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/two-edge-connected-components.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N,M);
	auto g=graph(N,M);
	TwoEdgeConnectedComponents tecd(g);

	auto tree=tecd.tree;
	auto grs=tecd.groups;

	vl belong(N);
	rep(i,grs.size())each(v,grs[i])belong[v]=i;
	Tree t(tree);
	auto path=t.path(belong[0],belong[1]);
	if(path.size()!=tree.size())die("No");
	assert(0);
	out("Yes");

	auto d0=bfs_restore(g,0);
	auto d1=bfs_restore(g,1);

	vl ans(N),bns(N);
	rep(i,N)ans[i]=d0[i].se;
	rep(i,N)bns[i]=d1[i].se;
	out(bns[0]+1);
	out(ans[1]+1);
	rep(i,2,N)out(ans[i]+1,bns[i]+1);
}
