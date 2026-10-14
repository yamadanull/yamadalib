#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,lim,C);
	ins(S);
	if(!YESNO(C*lim<=N))return;

	string ans;
	vl cur{0};
	auto dfs=[&](auto&& self)->void{
		if(cur.size()==C+1){
			rep(i,C){
				ll l=cur[i];
				ll r=cur[i+1];
				amax(ans,S.substr(l,r-l));
			}
			return;
		}
		rep(i,cur.back()+lim,N+1){
			cur.eb(i);
			self(self);
			cur.pop_back();
		}
	};
	dfs(dfs);
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
