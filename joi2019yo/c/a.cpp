#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ins(S);
	V<bool>fn(N);
	rep(i,N-1)if(!fn[i]){
		if(S.substr(i,2)=="OX" || S.substr(i,2)=="XO"){
			fn[i]=fn[i+1]=1;
		}
	}

	ll ans=0;
	each(f,fn)if(f)++ans;
	out(ans/2);
}
