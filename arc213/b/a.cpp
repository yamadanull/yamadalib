#include "../../template/template.hpp"
using namespace yamada;
const ll LG=60;

// [count(popcnt%2==0),count(popcnt%2==1)]
pl count01(ll N){
	vl dp0(LG+1); // Nに張り付いている popcnt%2==0
	vl dp1(LG+1); // Nに張り付いている popcnt%2==1
	vl ep0(LG+1); // Nに張り付いていない popcnt%2==0
	vl ep1(LG+1); // Nに張り付いていない popcnt%2==1
	dp0[LG]=1;
	repr(t,LG){
		if(N>>t&1){
			// 1にする
			{
				dp0[t]+=dp1[t+1];
				dp1[t]+=dp0[t+1];
				ep0[t]+=ep1[t+1];
				ep1[t]+=ep0[t+1];
			}
			// 0にする
			{
				ep0[t]+=dp0[t+1]+ep0[t+1];
				ep1[t]+=dp1[t+1]+ep1[t+1];
			}
		}
		else{
			// 1にする
			{
				ep0[t]+=ep1[t+1];
				ep1[t]+=ep0[t+1];
			}
			// 0にする
			{
				dp0[t]+=dp0[t+1];
				dp1[t]+=dp1[t+1];
				ep0[t]+=ep0[t+1];
				ep1[t]+=ep1[t+1];
			}
		}
	}
	return {ep0[0],ep1[0]};
}

ll cal0_lie(ll L,ll R){
	auto[cnt,dnt]=count01(R);
	auto[a,b]=count01(L);
	cnt-=a;
	dnt-=b;
	return max(cnt,dnt);
}

ll cal0(ll L,ll R){
	ll M=1; while(M*2<R)M*=2;
	bool dall=1;
	if(M<=L)dall=0;
	if(L+M<R)dall=0;

	if(dall==0)return cal0_lie(L,R);
	return cal0_lie(L,M)+cal0_lie(M,R);
}

string cal1_lie(ll L,ll R){
	ll cnt=0,dnt=0;
	rep(i,L,R){
		if(popcnt(i)%2)++cnt;
		else ++dnt;
	}

	string ans;
	rep(i,L,R){
		bool fn=0;
		if(popcnt(i)%2==1 && cnt>dnt)fn=1;
		if(popcnt(i)%2==0 && cnt<=dnt)fn=1;
		ans+=(fn? '1':'0');
	}
	return ans;
}

string cal1(ll L,ll R){
	ll M=1; while(M*2<R)M*=2;
	bool dall=1;
	if(M<=L)dall=0;
	if(L+M<R)dall=0;

	string ans;
	if(dall==0)return cal1_lie(L,R);
	return cal1_lie(L,M)+cal1_lie(M,R);
}

void yamada::solve()
{
	inl(T);
	while(T--){
		inl(q,L,R); ++R;
		repr(t,LG)if(R>>t&1){
			if(L>>t&1){
				L-=1LL<<t;
				R-=1LL<<t;
			}
			else break;
		}

		if(q==0)out(cal0(L,R));
		else out(cal1(L,R));
	}
}
