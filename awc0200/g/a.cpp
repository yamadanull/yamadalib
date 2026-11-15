#include "../../template/template.hpp"
#include "../../data-structure/union-find.hpp"

void yamada::solve()
{
	IN(N,M,A=LL*N);
	UnionFind uf(N);
	rep(M){
		IN(u,v); --u; --v;
		uf.unite(u,v);
	}

	vl ans(N);
	each(gr,uf.groups()){
		ll bns=0;
		each(u,gr){
			amax(bns,A[u]);
		}
		each(u,gr)ans[u]=bns;
	}
	each(a,ans)out(a);
}
