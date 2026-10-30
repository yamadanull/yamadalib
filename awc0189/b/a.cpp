#include "../../template/template.hpp"

void yamada::solve()
{
	ll ans=0;
	IN(N);
	rep(N){
		IN(x=CHR,d);
		ans+=(x=='L'?-d:d);
		out(ans);
	}
}
