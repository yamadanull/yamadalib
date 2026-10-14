#include "../../template/template.hpp"

constexpr int K=26;
void yamada::solve()
{
	inl(N);
	ins(S);
	string bns;
	rep(N)bns+=S;

	ll ans=-1;
	rep(d,1,N+1)if(N%d==0){
		bool fn=1;
		rep(i,N)if(S[i]!=S[(i+d)%N]){
			fn=0;
			break;
		}
		if(fn){
			ans=N/d;
			break;
		}
	}
	out(ans);
	out(bns.size());
	out(bns);
}
