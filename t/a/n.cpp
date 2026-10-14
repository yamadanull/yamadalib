#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	vl A(M); in(A);
	auto ans=mkiota(N);
	do{
		bool fn=1;
		rep(i,N-1){
			ll d=abs(ans[i+1]-ans[i]);
			bool gn=0;
			each(a,A)if(d%a==0){ gn=1; break; }
			if(!gn){ fn=0; break; }
		}
		if(fn)die("Yes");
	}while(nxp(ans));
	out("No");
}
void yamada::solve() { inl(T); while(T--)tc(); }
