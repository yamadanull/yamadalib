#include "../../template/template.hpp"

int dp[1<<27];

void yamada::solve()
{
	inl(N,W,D); D/=2;
	V<int> A(N); rep(i,1,N)in(A[i]);
	{
		int Dmx=0;
		for(int i=N-1; i>0; i-=W){
			Dmx+=i;
		}
		amin(D,Dmx);
	}

	auto idx=[&](int i,int d,int w)->ll{
		return (D+1)*(W+1)*i+(W+1)*d+w;
	};

	each(d,dp)d=-inf;

	dp[idx(1,0,0)]=0;
	rep(i,1,N)rep(d,D+1)rep(w,W+1)if(dp[idx(i,d,w)]>=0){
		ll id=idx(i,d,w);
		// ここで持って帰る
		if(d+i<=D && w<W){
			ll ID=idx(i+1,d+i,0);
			amax(dp[ID],dp[id]+A[i]);
		}

		// 持って次へ行く
		if(w<W){
			ll ID=idx(i+1,d,w+1);
			amax(dp[ID],dp[id]+A[i]);
		}
		// 持たずに次へ行く
		if(w<W){
			ll ID=idx(i+1,d,w);
			amax(dp[ID],dp[id]);
		}
	}

	int ans=-inf;
	rep(d,D+1)amax(ans,dp[idx(N,d,0)]);
	out(ans);
}
