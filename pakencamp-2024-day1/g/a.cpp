#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	inl(N,M); --M;
	ll n=N; // Nから2,3を除外した値
	ll cnt=0,dnt=0;
	while(n%2==0)n/=2,++cnt;
	while(n%3==0)n/=3,++dnt;

	if(M<=cnt){
		mint ans=N;
		rep(i,M)ans*=mint(3)/2;
		die(ans);
	}
	/* assert(0); */
	// ここよりあと

	assert(M>=1);
	if(cnt==0 && dnt==0){
		auto ds=divisors(N);
		N+=N/ds[1]; --M; // 問題設定ごと変える
		assert(N%2==0);

		n=N;
		if(M==0)die(mint(N));
		while(n%2==0)n/=2,++cnt;
		while(n%3==0)n/=3,++dnt;
		/* assert(0); */

		if(M<=cnt){
			mint ans=N;
			rep(i,M)ans*=mint(3)/2;
			die(ans);
		}
	}
	// これより前でwa
	/* assert(0); */

	M-=cnt; assert(M>=0);
	dnt+=cnt;
	cnt=0;
	ll state=(dnt-1)*3;

	mint ans=n;
	ll to=state+M;
	if(to%3==0){
		ans*=((mint)3).pow(to/3+1);
	}
	else if(to%3==1){
		ans*=4;
		ans*=((mint)3).pow(to/3);
	}
	else{
		ans*=2;
		ans*=((mint)3).pow(to/3+1);
	}
	out(ans);
}
