#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=1000;
	out(TC);
	while(TC--){
		ll N=randint(1,10);
		ll L=randint(1,10);
		ll K=randint(1,10);
		string S;
		rep(N)S+=randint(0,3)+'a';
		out(N,L,K);
		out(S);
	}
}
