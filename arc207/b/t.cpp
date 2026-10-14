#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../misc/random-graph.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N);
	vp es;
	rep(i,N)rep(j,i+1,N){
		es.eb(i,j);
	}

	rep(S,N-1,1LL<<es.size()){
		UnweightedGraph g(N);
		rep(i,es.size())if(S>>i&1){
			auto[u,v]=es[i];
			g[u].eb(v);
			g[v].eb(u);
		}

		bool fn=true;
		ll X=-1;
		rep(i,N){
			auto d=bfs(g,i);
			rep(j,N)if(d[j]<0){
				fn=false;
				break;
			}
			if(!fn)break;

			ll x=0;
			rep(j,N){
				if(d[j]==1 || d[j]==2)x+=j+1;
			}
			if(X>=0 && x!=X){ fn=false; break; }
			X=x;
		}
		if(fn){
			print(g);
			out(); cout.flush();
		}
	}
	out(-1);
}
