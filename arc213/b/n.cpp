#include "../../template/template.hpp"

void yamada::solve()
{
	inl(L,R); ++R;
	const ll LG=60;

	ll ans=-infLL;
	rep(msk,1,1<<(R-L)){
		bool fn=1;
		rep(i,R-L)if(msk>>i&1)rep(j,i+1,R-L)if(msk>>j&1){
			ll a=i+L;
			ll b=j+L;
			ll cnt=0;
			rep(t,LG){
				if((a>>t&1) != (b>>t&1)){
					++cnt;
				}
			}
			if(cnt<=1){
				fn=0;
				break;
			}
		}
		if(fn)amax(ans,popcnt(msk));
	}
	out(ans);
}
