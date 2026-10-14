#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	const ll N=2019;
	const ll L=TEN(15)*9;
	const ll R=TEN(16)+1;

	pl ans=mkp(94,9811608806490571);
	ll itr=1e7;
	while(itr--){
		ll l=randint(L,R-N);
		ll cnt=0;
		rep(i,l,l+N)if(is_prime(i))++cnt;
		amax(ans,mkp(cnt,l));
		if(itr%10000==0){
			out("残り:",itr);
			out(ans);
			cout.flush();
		}
	}
	out(ans.fi);
	out(ans.se,ans.se+N-1);

	/* ll cnt=0; */
	/* ll bns=9513063644776403LL; */
	/* rep(i,bns,bns+N)if(is_prime(i))++cnt; */
	/* out(bns,bns+N-1); */
	/* out(cnt); */
}
