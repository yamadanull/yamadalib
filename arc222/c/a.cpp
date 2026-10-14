#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vv(ll,A,N,N); in(A);
	vv(ll,B,N,N); // Aliceの最終位置ごとのコスト
	rep(i,N)rep(j,N){
		if(j>0)B[i][j]+=A[i][j-1];
		if(j<N-1)B[i][j]+=A[i][j+1];
	}
	vv(ll,dp,N,N,infLL); // こっから上だけの場合のコスト
	vv(ll,ep,N,N,infLL); // こっから下だけの場合のコスト
	rep(j,N)dp[0][j]=B[0][j];
	rep(j,N)ep[N-1][j]=B[N-1][j];
	rep(i,1,N)rep(j,N){
		if(j>0){
			amin(dp[i][j],dp[i-1][j-1]+B[i][j]);
		}
		if(j<N-1){
			amin(dp[i][j],dp[i-1][j+1]+B[i][j]);
		}
	}
	repr(i,N-1)rep(j,N){
		if(j>0){
			amin(ep[i][j],ep[i+1][j-1]+B[i][j]);
		}
		if(j<N-1){
			amin(ep[i][j],ep[i+1][j+1]+B[i][j]);
		}
	}

	vv(ll,ans,N,N);
	rep(i,N)rep(j,N){
		ll bns=infLL;
		rep(J,j-1,j+2,2)if(inLR(0LL,J,N)){
			amin(bns,dp[i][J]+ep[i][J]-B[i][J]);
		}
		ans[i][j]=bns;
	}
	each(a,ans)out(a);
}
void yamada::solve() { ini(T); while(T--)tc(); }
