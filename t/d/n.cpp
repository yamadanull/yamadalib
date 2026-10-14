#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../graph/graph-template.hpp"
using namespace yamada;

ll toU(string S){
	ll ans=0;
	reverse(all(S));
	each(c,S){
		ans*=3;
		if(c=='g')ans+=1;
		if(c=='d')ans+=2;
	}
	return ans;
}

void tc()
{
	ins(S,T);
	ll N=S.size();

	auto check=[](string S)->bool{
		ll N=S.size();
		rep(i,N-3)if(S.substr(i,4)=="good")return 0;
		return 1;
	};
	V<bool> vis(Power(3,N));
	auto dfs=[&](auto&& self)->void{
		ll u=toU(S);
		if(vis[u])return;
		vis[u]=1;
		rep(i,N-1){
			swap(S[i],S[i+1]);
			if(check(S))self(self);
			swap(S[i],S[i+1]);
		}
	};
	dfs(dfs);

	ll v=toU(T);
	YesNo(vis[v]);
}
void yamada::solve() { ini(T); while(T--)tc(); }
