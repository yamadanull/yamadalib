#include "../../template/template.hpp"

void yamada::solve()
{
	IN(S=STR);
	ll ans=0;
	each(c,S)if(c=='o')++ans;
	out(ans%2?"odd":"even");
}
