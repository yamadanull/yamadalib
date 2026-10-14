#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,K,M);
	if(!YESNO(K<=M))return;
	vl ans(N,1);
	rep(i,0,N,K){
		if(i%K==0)ans[i]+=M-K;
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
