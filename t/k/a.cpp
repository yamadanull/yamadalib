#include "../../template/template.hpp"
#include "../../misc/compress.hpp"
#include "../../atcoder/maxflow.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl X(N),Y(N); in2(X,Y);
	compress cmpx(X);
	compress cmpy(Y);

	atcoder::mf_graph<ll> g(cmpx.size()+cmpy.size()+2);
	ll Lsiz=cmpx.size();
	ll st=Lsiz+cmpy.size();
	ll go=st+1;
	rep(i,N){
		ll xi=cmpx(X[i]);
		ll yi=cmpy(Y[i]);
		g.add_edge(xi,yi+Lsiz,infLL);
	}
	rep(i,cmpx.size())g.add_edge(st,i,1);
	rep(i,cmpy.size())g.add_edge(i+Lsiz,go,1);

	out(g.flow(st,go));
}
void yamada::solve() { ini(T); while(T--)tc(); }
