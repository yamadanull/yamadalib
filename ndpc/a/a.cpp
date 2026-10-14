#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vv(ll,dp,N+1,3);
	dp[0][0]=1;
	rep(i,N){
		// はみ出し0からの繊維
		dp[i+1][0]+=dp[i][0]; // I
		dp[i+1][1]+=dp[i][0]*2; // L
		dp[i+1][2]+=dp[i][0]; // II

		// はみ出し1からの繊維
		dp[i+1][1]+=dp[i][1]; // I
		dp[i+1][2]+=dp[i][1]; // L

		// はみ出し2からの繊維
		dp[i+1][0]+=dp[i][2];
	}
	out(dp[N][0]);
}
