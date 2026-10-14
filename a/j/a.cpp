#include "../../template/multitest-template.hpp"
using namespace yamada;

ll count(vl &A){
	ll ans=0;
	ll N=A.size();
	vl dp(N+1);
	dp[0]=1;
	rep(a,4){
		vl ep(N+1);
		CumulativeSum cum(dp);
		rep(i,N)if(A[i]==a){
			ep[i+1]=cum(0,i+1);
		}
		dp=ep;
		err(a,dp);
	}
	return Sum(dp);
}

/* vl naive(ll X){ */
/* 	rep(len,1,infLL){ */
/* 		vl cur; */
/* 		auto dfs=[&](auto&& self)->bool{ */
/* 			if(cur.size()==len){ */
/* 				return count(cur)==X; */
/* 			} */
/* 			rep(i,4){ */
/* 				cur.eb(i); */
/* 				if(self(self))return 1; */
/* 				cur.pop_back(); */
/* 			} */
/* 			return 0; */
/* 		}; */
/* 		if(dfs(dfs))return cur; */
/* 	} */
/* 	return{}; */
/* } */

void output(vl &A){
	string S="NUPC";
	each(a,A)wout(S[a]);
	out();
}

void yamada::solve()
{
	inl(X);
	ll x=Isqrt(X);
	vl insert(x+1);
	{
		ll add=X-x*x;
		while(add>0){
			ll i=min(x,add);
			add-=i;
			insert[i]++;
		}
	}

	vl ans;
	rep(i,x){
		rep(insert[i])ans.eb(1);
		ans.eb(0);
	}
	rep(x+insert[x])ans.eb(1);
	ans.eb(2);
	ans.eb(3);
	output(ans);
	assert(count(ans)==X);
	assert(ans.size()<=x*2+20);
}
