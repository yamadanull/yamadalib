#include "../../template/template.hpp"
#include "../../shortest-path/dijkstra.hpp"

void yamada::solve()
{
	inl(N,M); --M;
	inl(go,st,ans); --st; --go;
	if(st==go)die(ans);
	auto g=wgraph<ll>(N,M,true);
	/* rep(u,N)each(e,g[u])out(u,e.to,e.cost); */

	ll bns=dijkstra(g,st)[go];
	if(bns<0)die(-1);
	/* out(st,go); */
	/* out(ans,bns); */
	out(ans+bns);
}
