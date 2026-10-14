#include "../../template/template.hpp"
#include "../../misc/all.hpp"
using namespace yamada;

void yamada::solve()
{
	ll TC=1000;
	out(TC);
	while(TC--){
		ll N=randint(3,100);
		ll K=randint(0,N*N+1);
		out(N,K);
	}
}
