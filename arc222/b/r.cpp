#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1);
	ll N=randint(3,16);
	ll a=randint(0,N+1);
	ll b=randint(0,N-a+1);
	ll c=N-a-b;
	out(a,b,c);
}
