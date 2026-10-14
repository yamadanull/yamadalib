#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	vl A(3); in(A); reverse(all(A));
	ll N=Sum(A);
	if(N>=16)return;

	ll ans=-infLL;
	rep(msk,1<<N){
		ll c=MSK(N)^msk;
		if(popcnt(c)!=A[2])continue;
		for(ll nsk=msk;;nsk=(nsk-1)&msk){
			/* out(msk,nsk); */
			ll a=nsk;
			ll b=msk^nsk;
			if(popcnt(a)==A[0]){
				assert(popcnt(b)==A[1]);

				vl belong(N);
				rep(i,N)if(b>>i&1)belong[i]=1;
				rep(i,N)if(c>>i&1)belong[i]=2;

				ll bns=0;
				rep(i,N){
					ll l=belong[modulo(i-1,N)];
					ll m=belong[i];
					ll r=belong[modulo(i+1,N)];
					if(m==modulo(l+1,3) && m==modulo(r+1,3))++bns;
				}
				amax(ans,bns);
				/* if(bns==5){ */
				/* 	out(belong); */
				/* } */
			}
			if(nsk==0)break;
		}
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
