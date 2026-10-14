#include "../../template/template.hpp"
#include "../../math/bigint-all.hpp"

void yamada::solve()
{
	const ll log=500;
	const ll N=1000;

	bigint a("1");
	rep(i,1,101){
		bigint b(i);
		a=a*b/GCDforBigintImpl::gcd_d_ary(a,b);
	}

	rep(i,1,N+1)out(a-i);
}
