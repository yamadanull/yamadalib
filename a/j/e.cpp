#include "../../template/template.hpp"
#include "../../prime/prime-enumerate.hpp"
#include "../../prime/fast-factorize.hpp"

void yamada::solve()
{
	ll N=1'000'000'000;
	auto ps=prime_enumerate(100);
	ll cnt=0;
	ll n=1;
	each(p,ps){
		n*=p;
		if(n>N)break;
		++cnt;
	}
	out(cnt);
}
