#include "../../template/template.hpp"

void yamada::solve()
{
	inl(a,b,c,d,e);
	ll ans=0;
	if(a<0){
		ans+=abs(a)*c+d;
		a=0;
	}
	ans+=(b-a)*e;
	out(ans);
}
