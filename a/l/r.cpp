#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	auto check=[&](auto lrc)->bool{
		ll N=lrc.size();
		vl cnt(N);
		each3(l,r,c,lrc)rep(d,l,r)cnt[d]++;
		return Max(cnt)<=5;
	};
	while(1){
		ll N=randint(2,10);
		vc<tuple<ll,ll,ll>> lrc;
		rep(N){
			ll l=randint(0,N-1);
			ll r=randint(l+1,N);
			ll c=randint(1,10);
			lrc.eb(l,r,c);
		}
		ll Q=1;
		vp ij(Q);
		each2(i,j,ij)i=randint(0,N-1),j=randint(i+1,N);

		if(check(lrc)){
			out(N,Q);
			each3(l,r,c,lrc)out(l+1,r,c);
			each2(i,j,ij)out(i+1,j+1);
			return;
		}
	}
}
