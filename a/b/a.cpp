#include "../../template/multitest-template.hpp"
using namespace yamada;

const int LG=30;
ll cal(vl A){
	ll N=len(A);
	if(Max(A)==0)return 0;
	ll m=0;
	each(a,A)amax(m,msb(a));
	each(a,A)if(msb(a)<m){
		return MSK(m+1);
	}
	each(a,A)a-=1<<m;
	return cal(A)+(1<<m);
}
void yamada::solve()
{
	IN(N,A=LL*N);
	out(cal(A));
}
