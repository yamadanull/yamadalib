#include "../../template/template.hpp"

void yamada::solve()
{
	ll N=5;
	IN(S=STR*N);
	ll ans=infLL;
	rep(2){
		S=RotateGrid(S);
		rep(i,N){
			ll cnt=0;
			each(c,S[i])if(c=='o')++cnt;
			amin(ans,N-cnt);
		}
		ll cnt=0;
		rep(i,N)if(S[i][i]=='o')++cnt;
		amin(ans,N-cnt);
	}
	out(ans);
}
