#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	ll x=-1;
	string ans;
	each(a,A){
		ans+=x<a?'o':'x';
		amax(x,a);
	}
	out(ans);
}
