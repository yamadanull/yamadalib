#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ins(S);
	vl A(N); in(A);
	auto dfs=[&](auto&& self,string S)->pl{
		vp lr;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && S[l]==S[r])++r;
			if(l>0 || S[l]=='.')lr.eb(l,r);
		}
		if(lr.size()<=1)return mkp(0,1);
		if(lr.size()%2==0)lr.pop_back();

		ll K=lr.size();
		vl val(K,-infLL),cnt(K);
		rep(k,K){
			auto[l,r]=lr[k];
			rep(i,l,r)amax(val[k],A[i]);
			rep(i,l,r)if(A[i]==val[k])++cnt[k];
		}

		ll ans=-infLL,bns=0;
		rep(k,1,lr.size(),2){
			auto[l,r]=lr[k];
			rep(i,l,r)S[i]='.';

			ll score=self(self,S).fi;
			score+=val[k-1]+val[k+1];

			rep(i,l,r)S[i]='#';
			if(score>ans){
				ans=score;
				bns=cnt[k-1]*cnt[k+1];
			}
			else if(score==ans)bns+=cnt[k-1]*cnt[k+1];
		}

		return {ans,bns};
	};
	auto[ans,bns]=dfs(dfs,S);
	out(bns);
}
