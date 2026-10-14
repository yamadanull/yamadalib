#include "../../template/template.hpp"

void yamada::solve()
{
	const ll log=30;
	inl(TC);
	while(TC--)
	{
		inl(C,X);
		if((X^C)>X){
			ll ans=(X^C);
			assert((ans^C)%ans==X);
			out(ans);
			continue;
		}

		ll cur=0;
		repr(t,log)if(C>>t&1){
			if(cur<X)cur+=1LL<<t;
			else cur-=1LL<<t;
			/* out("cur:",cur); */
		}
		if(cur==X){
			ll ans=1LL<<log;
			cur=0;
			repr(t,log)if(C>>t&1){
				if(cur<X){
					cur+=1LL<<t;
				}
				else{
					ans+=1LL<<t;
					cur-=1LL<<t;
				}
			}
			if(ans>0){
				assert((ans^C)%ans==X);
				out(ans);
			}
			else out(-1);
		}
		else out(-1);
	}
}
