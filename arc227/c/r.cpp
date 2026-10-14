#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,20);
	string S;
	rep(N)S+=randint(0,3)+'a';
	out(N);
	out(S);
}
