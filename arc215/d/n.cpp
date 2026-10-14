#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M); ++M;
	vvl ans;
	auto dfs=[&](auto&& self,vl A)->void{
		if(A.size()==N+1){
			vl S(N);
			rep(i,N)S[i]=A[i]+A[i+1];
			bool fn=1;
			rep(i,N-1)if(S[i]>S[i+1]){
				fn=0;
				break;
			}
			if(fn)ans.eb(S);
			return;
		}
		rep(i,M){
			A.eb(i);
			self(self,A);
			A.pop_back();
		}
	}; dfs(dfs,vl());

	out(mkuni(ans).size());
}
