#include "../../template/template.hpp"
#include "../../fps/ntt-friendly-fps.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
Binomial<mint> binom;
using fps = FormalPowerSeries<mint>;
void yamada::solve()
{
	inl(K); K-=6;
	if(K==0)die(4);
	// 各ブロックの重さの上限がiであるグラフの数
	V<mint> dp(K+1);

	fps F3(K+1);
	fps F2(K+1);
	fps F1(K+1); // 重さの和がi
	F3[0]=1;
	F2[0]=1;
	F1[0]=1;
	rep(i,1,K+1){
		mint cnt1=i+1;
		mint cnt2=cnt1*(i+1);
		mint cnt3=cnt2*(i+1);
		auto nF1=F1+(fps{cnt1}<<i).pre(K+1);
		auto nF2=F2+((F1*cnt1)<<i).pre(K+1)*2+(fps{cnt2}<<(i*2)).pre(K+1);
		auto nF3=F3+((F2*cnt1)<<i).pre(K+1)*3+((F1*cnt2)<<(i*2)).pre(K+1)*3+(fps{cnt3}<<(i*3)).pre(K+1);
		F1=nF1.pre(K+1);
		F2=nF2.pre(K+1);
		F3=nF3.pre(K+1);
		dp[i]=F3[K];
		/* out(F1); */
		/* out(F2); */
		/* out(F3); */
	}
	/* out(dp); */

	// 最大重みがiである通り数
	repr(i,1,K+1)dp[i]-=dp[i-1];
	mint ans=0;
	rep(i,K+1)ans+=dp[i]*(K-i+4);
	out(ans);
}
