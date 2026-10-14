#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,K);
	vl A(N); rep(i,N)A[i]=i;
	auto lis=[&](vl A)->ll{
		vl dp;
		each(a,A){
			ll pos=lb(dp,a);
			if(pos==dp.size())dp.eb(a);
			else dp[pos]=a;
		}
		return dp.size();
	};

	auto exlis=[&](vl A)->V<bool>{
		ll len=lis(A);
		V<bool> ans(N);
		rep(S,1<<N)if(popcnt(S)==len){
			vl B;
			rep(i,N)if(S>>i&1)B.eb(A[i]);
			bool fn=true;
			rep(i,len-1)if(B[i]>B[i+1])fn=false;
			if(fn){
				rep(i,N)if(S>>i&1)ans[i]=true;
			}
		}
		return ans;
	};

	auto exlds=[&](vl A)->V<bool>{
		reverse(all(A));
		auto ans=exlis(A);
		reverse(all(A));
		reverse(all(ans));
		return ans;
	};

	do{
		auto fn=exlis(A);
		auto gn=exlds(A);
		ll cnt=0;
		rep(i,N)if(fn[i]&&gn[i])++cnt;
		if(cnt==K)die(A);
	}while(nxp(A));
	die(-1);
}
