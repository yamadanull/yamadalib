#include "../../template/template.hpp"
using namespace yamada;

/* bool check(vl ans,ll K){ */
/* 	ll N=ans.size(); */
/* 	UnweightedGraph g(N); */
/* 	rep(i,N-1){ */
/* 		g[ans[i]].eb(ans[i+1]); */
/* 		g[ans[i+1]].eb(ans[i]); */
/* 	} */

/* 	VV<int> dp; */
/* 	rep(i,N)dp.eb(bfs(g,i)); */
/* 	ll dist=0; */
/* 	rep(i,N){ */
/* 		ll d=dp[i][(i+1)%N]; */
/* 		if(d<0)return 0; */
/* 		dist+=dp[i][(i+1)%N]; */
/* 	} */
/* 	return dist==K; */
/* } */

void tc()
{
	inl(N,K);
	if(K%2)die(-1);
	if(K<(N-1)*2)die(-1);
	if(N%2){
		ll n=N/2;
		if(K>n*(n+1)*2)die(-1);
	}
	else{
		ll n=N/2-1;
		if(K>n*(n+1)*2+N)die(-1);
	}

	vl ans(N);
	auto dfs=[&](auto&& self,ll L,ll R,ll k)->void{
		ll n=R-L;
		assert(k>=(n-1)*2);
		if(n==1){
			assert(k==0);
			return;
		}
		if(n==2){
			assert(k==2);
			ans[L+1]=1;
			return;
		}

		if(k>=(n-1)*4){
			ans[L]=n-2;
			ans[R-1]=n-1;
			self(self,L+1,R-1,k-(n-1)*2);
			return;
		}

		ll D=(k-(n-1)*2)/2;
		assert(D<=n-2);
		if(D==n-2){
			assert(n>=6);
			rep(i,L,R)ans[i]=i-L;
			reverse(ans.begin()+L+1,ans.begin()+R-1);
			swap(ans[L+2],ans[L+3]);
		}
		else{
			rep(i,L,R)ans[i]=i-L;
			reverse(ans.begin()+L+1,ans.begin()+L+2+D);
		}
	};
	dfs(dfs,0,N,K);

	rep(i,N-1)fout(ans[i]+1,ans[i+1]+1);
	/* assert(check(ans,K)); */
}
void yamada::solve() { ini(T); while(T--)tc(); }
