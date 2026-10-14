#include "../../template/template.hpp"
using namespace yamada;

/* ll val(vl A){ */
/* 	ll N=A.size(); */
/* 	auto B=A; */
/* 	rep(i,1,N)B[i]^=B[i-1]; */
/* 	return Sum(B); */
/* } */

void tc()
{
	inl(N);
	vl ans;
	rep(i,1,N+1){
		if(i%4==2)ans.eb(i+1);
		else if(i%4==3)ans.eb(i-1);
		else ans.eb(i);
	}
	if(N%4==2){
		ans.back()--;
	}
	out(ans);
	/* out(val(ans)); */
}
void yamada::solve() { ini(T); while(T--)tc(); }
