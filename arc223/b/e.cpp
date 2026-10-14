#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,K);
	set<vl> vis;
	auto dfs=[&](auto&& self,vl A)->void{
		if(vis.find(A)!=vis.end())return;
		vis.insert(A);
		rep(i,N-1){
			if((A[i]+A[i+1])%K==0){
				swap(A[i],A[i+1]);
				self(self,A);
				swap(A[i],A[i+1]);
			}
		}
	};
	out();
	vl A(N); in(A);
	dfs(dfs,A);
	each(a,vis)out(a);
}
void yamada::solve() { ini(T); while(T--)tc(); }
