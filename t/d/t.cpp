#include "../../template/template.hpp"

void yamada::solve()
{
	const ll N=5;
	const ll M=5;
	map<vl,pl>memo;
	memo[vl(N,0)]=mkp(0,0);
	auto cal=[&](auto&& self,vl &A)->pl{
		if(memo.count(A))return memo[A];
		vp lr;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && A[l]==A[r])++r;
			lr.eb(l,r);
		}

		ll ans=0;
		each2(l,r,lr)if(A[l]>0){
			rep(i,l,r)--A[i];
			ll nans=self(self,A).se+(r-l);
			amax(ans,nans);
			rep(i,l,r)++A[i];
		}
		return memo[A]=mkp(ans,Sum(A)-ans);
	};

	auto dfs=[&](auto&& self,vl A)->void{
		if(A.size()==N){
			out("A:",A);
			out("ans:",cal(cal,A));
			return;
		}
		ll st=(A.empty()? 1:A.back());
		rep(i,st,M){
			A.eb(i);
			self(self,A);
			A.pop_back();
		}
	}; dfs(dfs,vl());
}
