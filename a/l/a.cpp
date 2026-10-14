#include "../../template/template.hpp"

const int M=1'000'000'000;
void yamada::solve()
{
	auto quest=[&](ll x)->ll{
		fout("?",x+1);
		inl(s);
		return s;
	};
	auto answer=[&](vl ans){
		each(a,ans)++a;
		fout("!",ans);
	};
	inl(N);
	ll S=quest(0);
	vl ans(N);
	auto dfs=[&](auto&& self,ll L,ll R,ll cntL,ll sumL,ll cnt,ll sum)->void{
		err(L,R,cntL,sumL,cnt,sum);
		if(cnt==1){
			ans[cntL]=sum;
			return;
		}
		ll x=sum/cnt+1;
		ll s0=quest(x-1);
		ll s1=quest(x);
		ll cnt0x=-1;
		{
			ll ds=s1-s0; // cnt(0,x)-cnt(x,M)
			cnt0x=(ds+N)/2;
		}
		ll sum0x=((cnt0x*2-N)*x-s1+S)/2;
		ll sumLx=sum0x-sumL;
		ll cntLx=cnt0x-cntL;
		assert(inLR(1,cntLx,cnt));
		self(self,L,x,cntL,sumL,cntLx,sumLx);
		self(self,x,R,cntL+cntLx,sumL+sumLx,cnt-cntLx,sum-sumLx);
	};
	dfs(dfs,0,M,0,0,N,S);

	answer(ans);
}
