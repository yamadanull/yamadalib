#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,x,y);
	if(__gcd(x,y)==1)out(1);
	else out(2);
}
