#include "../../template/template.hpp"
#include "../../tree/tree-query.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	inl(N,Q);
	vl A(N); in(A);
	auto g=graph(N);
	Tree t(g);
	while(Q--){
		inl(u,v); --u; --v;
		auto path=t.path(u,v);
		ll pn=path.size();

		ll ans=0;
		rep(l,pn)rep(r,l,pn){
			ll xo=0,sm=0;
			rep(pi,l,r+1){
				xo^=A[path[pi]];
				sm+=A[path[pi]];
			}
			if(xo>=sm)++ans;
		}
		out(ans);
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
