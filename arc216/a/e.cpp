#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	constexpr ll N=5;
	/* inl(N); */
	UnweightedGraph g(1<<N);
	rep(msk,1<<N){
		/* if(!(msk&1))continue; */
		/* if((msk>>(N-1)&1))continue; */
		rep(i,1,N-1){
			bool b0=msk>>(i-1)&1;
			bool b1=msk>>(i+1)&1;
			if(b0==b1){
				ll nsk=msk^(1<<i);
				g[msk].eb(nsk);
			}
		}
	}

	rep(u,1<<N){
		auto dp=bfs(g,u);
		rep(v,1<<N)if(dp[v]>=1){
			out(bitset<N>(u),bitset<N>(v),":",dp[v]);
		}
	}

	/* each(gr,uf.groups()){ */
	/* 	sort(all(gr)); */
	/* 	V<bitset<N>> bs; */
	/* 	each(u,gr)bs.eb(u); */
	/* 	out(bs[0]); */
	/* } */
}
void yamada::solve() { ini(T); while(T--)tc(); }
