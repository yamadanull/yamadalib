#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=1;
	out(TC);
	rep(TC){
		ll N=randint(1,5);
		ll M=randint(1,5);
		string S,T;
		rep(N)S+=randint(0,2)?'W':'R';
		rep(M)T+=randint(0,2)?'W':'R';

		out(N,M);
		out(S);
		out(T);
	}
}
