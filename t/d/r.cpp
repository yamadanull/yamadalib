#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll TC=2000;
	out(TC);
	while(TC--){
		ll N=randint(1,100);
		V<tuple<ll,ll,ll>> es;
		rep(i,N)rep(j,i,N)if(!randint(0,10)){
			ll op=randint(1,3);
			es.eb(op,i,j);
		}
		ll M=es.size();

		out(N,M);
	}
}
