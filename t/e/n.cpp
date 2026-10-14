#include "../../template/template.hpp"
using namespace yamada;

ll dp[31][2][2][2][2];
ll cal_same(ll L,ll R){
	ll LG=Digit(L,2).size();

	each(d4,dp)each(d3,d4)each(d2,d3)each(d1,d2)each(d,d1)d=infLL;
	dp[LG][1][1][1][1]=0;

	// fL,gL: 張り付きの有無
	repr(t,LG)rep(fL,2)rep(gL,2)rep(fR,2)rep(gR,2)if(dp[t+1][fL][gL][fR][gR]<infLL){
		ll l=L>>t&1;
		ll r=R>>t&1;
		rep(f,2)rep(g,2){
			if(f<l && fL)continue;
			if(f>r && fR)continue;
			if(g<l && gL)continue;
			if(g>r && gR)continue;
			ll FL=fL,GL=gL,FR=fR,GR=gR;
			if(f>l)FL=0;
			if(f<r)FR=0;
			if(g>l)GL=0;
			if(g<r)GR=0;
			amin(dp[t][FL][GL][FR][GR],dp[t+1][fL][gL][fR][gR]*2+(f&g));
		}
	}
	ll ans=infLL;
	each(d3,dp[0])each(d2,d3)each(d1,d2)each(d,d1)amin(ans,d);
	return ans;
}

void answer(pl ab,ll N){
	auto[a,b]=ab;
	auto diga=Digit(a,2); reverse(all(diga));
	auto digb=Digit(b,2); reverse(all(digb));
	ll n=diga.size();
	ll m=digb.size();

	string S;
	ll T=n*m;
	rep(i,T){
		if(diga[i%n] & digb[i%m])S+='1';
		else S+='0';
	}
	string ans;
	while(ans.size()<N)ans+=S;
	while(ans.size()>N)ans.pop_back();
	out(ans);
}

void tc()
{
	inl(L,R,N); // CLOSED!!!!!!!!!!!!

	ll n=Digit(L,2).size();
	ll m=Digit(R,2).size();
	if(n+2<=m){
		ll a=1LL<<m-1;
		ll b=1LL<<m-2;
		answer({a,b},N);
	}
	else if(n+1==m){
		ll a=1LL<<m-1;
		answer({a,L},N);
	}
	else{
		auto a=cal_same(L,R);
		answer({a,a},N);
	}
	cout.flush();
}
void yamada::solve() { ini(T); while(T--)tc(); }
