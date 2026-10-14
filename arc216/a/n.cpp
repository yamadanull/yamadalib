#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	UnweightedGraph g(1<<N);
	rep(msk,1<<N){
		rep(i,1,N-1){
			bool b0=msk>>(i-1)&1;
			bool b1=msk>>(i+1)&1;
			if(b0==b1){
				ll nsk=msk^(1<<i);
				g[msk].eb(nsk);
			}
		}
	}

	ins(A,B);
	ll st=0,go=0;
	rep(i,N)if(A[i]=='1')st|=1<<i;
	rep(i,N)if(B[i]=='1')go|=1<<i;
	auto dp=bfs(g,st);
	out(dp[go]);
	/* YesNo(dp[go]>=0); */

	/* each(gr,uf.groups()){ */
	/* 	sort(all(gr)); */
	/* 	V<bitset<N>> bs; */
	/* 	each(u,gr)bs.eb(u); */
	/* 	out(bs[0]); */
	/* } */
}
void yamada::solve() { ini(T); while(T--)tc(); }
