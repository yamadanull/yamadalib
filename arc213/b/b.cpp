#include "../../template/template.hpp"
using namespace yamada;

void yamada::solve()
{
	const ll LG=60;
	inl(L,R); ++R;
	repr(t,LG)if(R>>t&1){
		if(L>>t&1){
			L-=1LL<<t;
			R-=1LL<<t;
		}
		else{
			break;
		}
	}
	ll M=1;
	while(M*2<R)M*=2;

	bool dall=1;
	if(M<=L)dall=0;
	if(L+M<R)dall=0;

	if(dall==0){
		ll cnt=0,dnt=0;
		rep(i,L,R){
			if(popcnt(i)%2)++cnt;
			else ++dnt;
		}
		out(max(cnt,dnt));
	}
	else{
		ll ans=0;
		{
			ll cnt=0,dnt=0;
			rep(i,L,M){
				if(popcnt(i)%2)++cnt;
				else ++dnt;
			}
			ans+=max(cnt,dnt);
		}

		{
			ll cnt=0,dnt=0;
			rep(i,M,R){
				if(popcnt(i)%2)++cnt;
				else ++dnt;
			}
			ans+=max(cnt,dnt);
		}
		out(ans);
	}
}
