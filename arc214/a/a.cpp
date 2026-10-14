#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vs S(N); in(S);
	rep(d,N*2-1){
		ll c=-1;
		rep(i,N){
			ll j=d-i;
			if(!inLR(0LL,j,N))continue;
			if(S[i][j]!='?'){
				if(c>=0)if(c!=S[i][j]-'0')die(-1);
				c=S[i][j]-'0';
			}
		}

		if(c<0)c=0;
		rep(i,N){
			ll j=d-i;
			if(!inLR(0LL,j,N))continue;
			S[i][j]=c+'0';
		}
	}

	each(s,S)out(s);
}
