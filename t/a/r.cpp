#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll T=100;
	out(T);

	while(T--){
		ll N=randint(3,500);
		ll M=randint(1,10);
		vl D(M);
		each(a,D)a=randint(0,N/3)+1;

		out(N,M);
		out(D);
		cout.flush();

		/* vl ans(N); */
		/* in(ans[0]); */
		/* if(ans[0]==-1)continue; */
		/* rep(i,1,N)in(ans[i]); */
		/* rep(i,N-1){ */
		/* 	ll a=abs(ans[i+1]-ans[i]); */
		/* 	bool fn=0; */
		/* 	each(d,D)if(a%d==0)fn=1; */
		/* 	assert(fn); */
		/* } */
	}
}
