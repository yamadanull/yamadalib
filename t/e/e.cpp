#include "../../template/template.hpp"
using namespace yamada;

ll cal(ll msk,ll N){
	V<bool> A(N);
	rep(i,N)if(msk>>i&1)A[i]=1;
	vv(ll,dp,N+1,3,infLL);
	rep(j,3)dp[0][j]=0;
	rep(i,N)rep(j,3){
		ll add=(A[i]==j%2? 0:1);
		rep(k,j,3){
			amin(dp[i+1][k],dp[i][j]+add);
		}
	}
	return dp[N][2];
}

void tc()
{
	auto toS=[&](ll msk,ll N)->string{
		string ans;
		rep(i,N){
			if(msk>>i&1)ans+='#';
			else ans+='.';
		}
		return ans;
	};
	inl(N);
	rep(msk,1<<N){
		out(toS(msk,N),":",cal(msk,N));
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
