#include "../../template/template.hpp"
#include "../../graph/strongly-connected-components.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

ll cal(vl A){
	ll N=A.size();
	if(N<=1)return 0;
	vl B;
	ll M=A[0]+1;
	rep(i,N)if(A[i]>A[0])B.eb(A[i]-M);

	ll ans=cal(B);
	ans*=1<<(M);
	ans+=MSK(M-1);
	return ans;
}

void yamada::solve()
{
	inl(n);
	map<vl,ll> mp;
	vvl As;
	{
		vl A(n);
		rep(i,n)A[i]=i;
		do{
			mp[A]=As.size();
			As.eb(A);
		}while(nxp(A));
	}

	ll N=As.size();
	UnweightedGraph g(N);
	rep(u,N){
		auto&& A=As[u];
		ll mx=A[0];
		rep(i,1,n){
			if(!amax(mx,A[i])){
				vl B{A[i]};
				rep(j,n)if(i!=j)B.eb(A[j]);
				ll v=mp[B];
				/* out(u,v); */
				g[v].eb(u);
			}
		}
	}

	vl dist(N);
	StronglyConnectedComponents scc(g);
	rep(si,N){
		ll u=scc.belong(si)[0];
		each(v,g[u]){
			amax(dist[v],dist[u]+1);
		}
	}

	vvl grs(Max(dist)+1);
	rep(u,N)grs[dist[u]].eb(u);
	rep(d,grs.size()){
		out();
		out(d);
		/* out(Digit(d,2,n-1),":"); */
		each(u,grs[d]){
			out(As[u]);
			assert(cal(As[u])==d);
		}
	}
}
