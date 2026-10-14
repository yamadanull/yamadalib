#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=500;
	ll M=500;
	ll Q=0;
	vs S(N);
	each(s,S)rep(M)s+=randint(0,2)+'0';

	out(N,M,Q);
	each(s,S)out(s);
}
