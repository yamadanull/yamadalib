#include "../../template/multitest-template.hpp"
using namespace yamada;

void exper(){
	IN(N);
	map<vc<int>,bool> vis;
	vis[mkiota(N)]=1;
	queue<vc<int>> q;
	q.emplace(mkiota(N));
	map<vc<int>,vvc<int>> ans;
	while(!q.empty()){
		auto P=q.front(); q.pop();
		ans[P|Stride(2)|rtov].eb(P|Drop(1)|Stride(2)|rtov);
		rep(l,N-3){
			swap(P[l],P[l+2]);
			swap(P[l+1],P[l+3]);
			if(!vis[P]){
				vis[P]=1;
				q.emplace(P);
			}
			swap(P[l],P[l+2]);
			swap(P[l+1],P[l+3]);
		}
	}

	each(P_,PS_,ans){
		auto P=P_;
		auto PS=PS_;
		each(e,P)e/=2;
		each(e,PS|Join)e/=2;
		err();
		err(P);
		each(p,PS)err("",p);
	}
}

void yamada::solve()
{
	/* exper(); */
	IN(S=STR,T=STR);
}
