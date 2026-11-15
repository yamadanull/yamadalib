#include "../../template/template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(S=STR,X=STR,Y=STR);
	ll N=len(S);
	ll M=len(X);
	ll K=len(Y);
	VVV(mint,dp,N+1,1<<M,1<<K,0);
	dp[0][1<<M-1][0]=1;

	vl memox(2,MSK(M)),memoy(2,MSK(K)); // 最後の文字がjとしてありえる状態
	rep(i,M)if(X[i]!='?'){ll j=X[i]-'0';memox[1-j]&=~(1<<i);}
	rep(i,K)if(Y[i]!='?'){ll j=Y[i]-'0';memoy[1-j]&=~(1<<i);}
	rep(i,N)rep(mskx,1<<M)rep(msky,1<<K)if(dp[i][mskx][msky]!=0){
		if(i<5)err(i,mskx,msky,dp[i][mskx][msky]);
		rep(p,2){
			if(S[i]!='?'&&S[i]-'0'!=p)continue;
			ll nskx=mskx<<1&MSK(M)&memox[p];
			ll nsky=msky<<1&MSK(K)&memoy[p];
			if(mskx>>M-1&1)nskx|=1&memox[p],nsky|=1&memoy[p];
			if(msky>>K-1&1)nskx|=1&memox[p];
			dp[i+1][nskx][nsky]+=dp[i][mskx][msky];
		}
	}
	mint ans=0;
	rep(mskx,1<<M)rep(msky,1<<K)if(mskx>>M-1&1||msky>>K-1&1){
		ans+=dp[N][mskx][msky];
	}
	out(ans);
}
