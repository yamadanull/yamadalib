#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(3,15);
	string A,B;
	rep(N)A+=randint(0,2)+'0';
	rep(N)B+=randint(0,2)+'0';
	out(N,A,B);
}
