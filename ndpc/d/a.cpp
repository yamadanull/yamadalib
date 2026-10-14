#include "../../template/template.hpp"
using namespace yamada;

constexpr int BS=10;
void tc()
{
	inl(N);
	auto dig=Digit(N,BS);
	ll n=dig.size();

	vl dp(n+1,infLL); // 値がそのまま
	vl ep(n+1,infLL); // 値が1増えている
	dp[0]=0;
	rep(i,n){
		// 値そのままから減らす
		amin(dp[i+1],dp[i]+dig[i]);
		// 値そのままから増やす
		amin(ep[i+1],dp[i]+BS-dig[i]);

		// 値増えてて減らす
		if(dig[i]==BS-1){
			amin(ep[i+1],ep[i]);
		}
		else amin(dp[i+1],ep[i]+dig[i]+1);

		// 値増えてて増やす
		if(dig[i]==BS-1);
		else amin(ep[i+1],ep[i]+BS-(dig[i]+1));
	}

	/* out(dp); */
	/* out(ep); */
	ll ans=dp[n];
	ll bns=ep[n]+1;
	out(min(ans,bns));
}
void yamada::solve() { ini(T); while(T--)tc(); }
