#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=1;
	/* out(TC); */
	rep(TC){
		ll N=2499;
		vl A{4,8,6,9};
		string S;
		rep(N)S+=A[randint(0,3)]+'0';
		out(S);
	}
}
