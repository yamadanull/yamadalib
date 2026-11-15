#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,K);
	string ans;
	bool a=1;
	rep(i,0,N,K){
		ll r=min(i+K,N);
		rep(r-i)ans+=a?'R':'B';
		a^=1;
	}
	out(ans);
}
