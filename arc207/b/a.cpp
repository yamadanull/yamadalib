#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(N);
	if(N<=5)die(-1);

	vp ans;
	ans.eb(1,2);
	ans.eb(2,3);
	ans.eb(3,6);
	ans.eb(6,5);
	ans.eb(5,4);
	ans.eb(4,1);
	rep(i,7,N+1){
		ll L=(i%2)+1;
		ll R=i;
		if(i%2==0)--R;
		ll from=(i%2? i:0);
		rep(j,L,R,2){
			ans.eb(from,j);
		}
		if(i%2==0){
			each2(u,v,ans)u++,v++;
		}
	}

	out(ans.size());
	each(e,ans)out(e);
	return;

	{
		UnweightedGraph g(N);
		each2(u,v,ans){
			--u; --v;
			g[u].eb(v);
			g[v].eb(u);
		}

		bool fn=true;
		ll X=-1;
		rep(i,N){
			auto d=bfs(g,i);
			rep(j,N)if(d[j]<0){
				fn=false;
			}

			ll x=0;
			rep(j,N){
				if(d[j]==1 || d[j]==2)x+=j+1;
			}
			if(X>=0 && x!=X){ fn=false;}
			X=x;
		}
		assert(fn);
	}
}
