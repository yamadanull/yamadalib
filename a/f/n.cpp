#include "../../template/template.hpp"
using namespace yamada;

bool naive(ll A,ll B,ll C){
	auto res=[&](ll u)->tuple<ll,ll,ll>{
		ll ans=u/(B*C);
		u%=(B*C);
		ll bns=u/C;
		u%=C;
		return{ans,bns,u};
	};

	vl X{1,2,3};
	vvv(bool,dp,A,B,C);
	map<VVV<bool>,bool> mp;
	auto dfs=[&](auto&& self,ll u)->bool{
		auto[I,J,K]=res(u);
		if(I==A)return 1;
		if(dp[I][J][K])return self(self,u+1);
		if(mp.count(dp))return mp[dp];

		bool ans=0;
		auto F=[&](auto P){
			auto x=X;
			rep(i,3)x[i]=X[P[i]];
			bool fn=1;
			rep(i,I,I+x[0])rep(j,J,K+x[1])rep(k,K,K+x[2]){
				if(!inLR(0LL,i,A))fn=0;
				else if(!inLR(0LL,j,B))fn=0;
				else if(!inLR(0LL,k,C))fn=0;
				else if(dp[i][j][k])fn=0;
			}
			if(!fn)return;
			rep(i,I,I+x[0])rep(j,J,K+x[1])rep(k,K,K+x[2])dp[i][j][k]=1;
			ans|=self(self,u+1);
			rep(i,I,I+x[0])rep(j,J,K+x[1])rep(k,K,K+x[2])dp[i][j][k]=0;
		};
		nxp(3,F);
		return mp[dp]=ans;
	};
	return dfs(dfs,0);
}

void yamada::solve()
{
	ll N=3;
	inl(a,b,c);
	/* vl A{a,b,c}; */
	/* bool ans=0; */
	/* rep(i,N)if(A[i]%2==0)rep(j,N)if(A[j]%3==0)if(i!=j){ */
	/* 	ans=1; */
	/* } */
	/* if((a*b*c)%6==0 && (a+b+c)%6==0)ans=1; */
	/* YesNo(ans); */
	YesNo(naive(a,b,c));
}
