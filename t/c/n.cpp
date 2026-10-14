#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	ll st=0,go=0;
	rep(i,N){
		inl(a);
		if(a)st|=1<<i;
	}
	rep(i,N){
		inl(b);
		if(b)go|=1<<i;
	}

	UnweightedGraph g(1<<N);
	rep(msk,1<<N)rep(nsk,1<<N){
		ll cnt=0;
		rep(i,N)if(msk>>i&1)if(!(nsk>>i&1))++cnt;
		if(cnt%2)g[msk].eb(nsk);
	}

	out(bfs(g,st)[go]);
}
void yamada::solve() { ini(T); while(T--)tc(); }
