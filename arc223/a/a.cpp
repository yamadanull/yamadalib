#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,W);
	vl w(N),v(N); in2(w,v);
	auto wrui=mkrui(w);
	auto vrui=mkrui(v);
	auto dfs=[&](auto&& self,ll R,ll W)->ll{
		if(R<0)return 0;
		if(w[R]>W)return self(self,R-1,W);
		ll ans=vrui[R];
		amax(ans,v[R]+self(self,R-1,W-w[R]));
		return ans;
	};

	out(dfs(dfs,N-1,W));
}
void yamada::solve() { ini(T); while(T--)tc(); }
