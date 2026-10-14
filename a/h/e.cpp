#include "../../template/template.hpp"
using namespace yamada;

int LG;
ll f(ll x,ll y){
	ll ans=0;
	ll a=x&y;
	ll b=x|y;
	rep(t,LG){
		if(t%2==0){
			ans|=(a>>t&1)<<t;
		}
		else{
			ans|=(b>>t&1)<<t;
		}
	}
	return ans;
}

string bin(ll N){
	string ans;
	repr(t,LG){
		if(N>>t&1)ans+='#';
		else ans+='.';
	}
	return ans;
}

void yamada::solve()
{
	in(LG);
	ll N=1<<LG;
	vl G(N);
	vl cnt(N);
	// i追加
	rep(i,N-1){
		rep(j,i)cnt[f(j,i)]+=2;
		cnt[i]++;

		ll mx=Max(cnt);
		rep(g,cnt.size())if(cnt[g]==mx){
			G[i+1]=g;
			break;
		}
	}
	for(ll l=1,r=1; l<N; l=r){
		while(r<N && G[l]==G[r])++r;
		out(l);
		/* out(bin(l),"~",bin(r-1),":",bin(G[l])); */
	}
}
