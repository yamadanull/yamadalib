#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,10);
	ll Q=randint(1,10);
	string S;
	rep(N)S+='a'+randint(0,10);

	out(N,Q,S);
	while(Q--){
		ll op=randint(1,3);
		if(op==1){
			ll k=randint(0,N);
			ll l=randint(0,N);
			ll r=randint(l+1,N+1);
			out(op,k+1,l+1,r);
		}
		else{
			ll i=randint(0,N);
			ll j=randint(0,N);
			out(op,i+1,j+1);
		}
	}
}
