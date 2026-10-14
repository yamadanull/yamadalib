#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	auto g=graph(N,M,true);
	vl cnt(N);
	rep(u,N)each(v,g[u])++cnt[v];

	vl A(N); in(A); each(a,A)--a;
	vl pos(N); rep(i,N)pos[A[i]]=i;
	minpq<ll> q;
	rep(i,N)if(cnt[i]==0){
		q.push(A[i]);
	}

	ll ans=0;
	while(!q.empty()){
		vl del;
		del.eb(q.top()); q.pop();
		while(!q.empty()){
			ll a=q.top();
			if(a==del.back()+1){
				del.eb(a);
				q.pop();
			}
			else break;
		}

		ans+=del.size()-1;
		each(a,del){
			ll u=pos[a];
			each(v,g[u]){
				if(--cnt[v]==0){
					q.push(A[v]);
				}
			}
		}
	}
	out(ans);
}

void yamada::solve() { inl(T); while(T--)tc(); }
