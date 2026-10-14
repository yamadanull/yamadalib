#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M);
	vs S(N); in(S);
	V<bool> fn(N,0);
	string ans;
	rep(j,M){
		ll cnt=0,dnt=0;
		rep(i,N)if(!fn[i]){
			if(S[i][j]=='0')++cnt;
			else ++dnt;
		}
		if(cnt>=dnt)ans+='0';
		else ans+='1';
		rep(i,N)if(S[i][j]==ans.back())fn[i]=1;
	}
	each(f,fn)if(!f)die("No");
	out("Yes");
	out(ans);
}
