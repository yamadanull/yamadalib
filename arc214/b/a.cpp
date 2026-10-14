#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N,M);
	/* out("A"); cout.flush(); */
	auto g=wgraph<ll>(N,M);
	/* out("A"); cout.flush(); */
	UnionFind uf(N);
	rep(u,N)each(v,g[u])uf.unite(u,v);

	vl A(N+1); rep(i,N+1)A[i]=i;
	vl ans;
	do{
		bool fn=1;
		rep(u,N){
			each(v,g[u]){
				if((A[u]^A[v])!=v.cost){
					fn=0;
					break;
				}
			}
			if(!fn)break;
		}
		if(fn){
			out(A);
			ans.eb(A.back());
		}
	}while(nxp(A));

	ans=mkuni(ans);
	out(ans); cout.flush();
	if(uf.size(0)<N)assert(ans.size()>=2);
}
