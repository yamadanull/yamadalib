#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N,K);
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	vv(bool,vis,N,N);
	auto dfs=[&](auto&& self,ll i,ll j,ll cur,ll dep)->bool{
		if(dep==N*N-1)return cur==K && i==N-1 && j==N-1;
		vis[i][j]=1;
		rep(x,4){
			ll I=i+di[x];
			ll J=j+dj[x];
			if(!inLR(0LL,I,N))continue;
			if(!inLR(0LL,J,N))continue;
			if(vis[I][J])continue;
			ll dur=cur; if(x==3)++dur;
			if(self(self,I,J,dur,dep+1))return 1;
		}
		vis[i][j]=0;
		return 0;
	};
	YesNo(dfs(dfs,0,0,0,0));
}
