#include "../../template/multitest-template.hpp"
using namespace yamada;

map<pl,bool> mp;
bool naive(ll N,ll msk){
	/* err(N,msk); */
	if(mp.count(mkp(N,msk)))return mp[mkp(N,msk)];
	rep(nsk,1,1<<N){
		if(![&]()->bool{
			if(popcnt(nsk)==1)return 1;
			ll c=0;
			rep(i,N)if(nsk>>i&1)if(msk>>i&1)c++;
			return c%2==0;
		}())continue;

		ll ksk=0;
		ll curt=0;
		rep(i,N)if(!(nsk>>i&1)){
			ksk|=1LL<<curt++;
		}
		if(!naive(curt,ksk))return mp[mkp(N,msk)]=1;
	}
	return mp[mkp(N,msk)]=0;
}
bool naive(ll N,vl A){
	ll msk=0;
	each(i,a,A|Enumerate)if(a%2)msk|=1LL<<i;
	return naive(N,msk);
}
bool cal(ll N,vl A){
	if(N==1 || N>=4)return 1;
	ll c=0;
	each(a,A)c+=a%2;
	if(N==2)return c%2==0;
	// N==3
	return c!=3;
}

void exper(){
	IN(N);
	rep(msk,1<<N){
		err(tog(msk,N),naive(N,msk));
	}
}

void yamada::solve()
{
	exper();
	/* IN(N,A=LL*N); */
	/* out(cal(N,A)? "Moggity":"Larpity"); */
}
