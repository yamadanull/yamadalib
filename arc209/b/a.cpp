#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	// 偶数ブロックが高々1個の同じぐらいのブロックに分割
	auto part=[](ll X,ll Bcnt)->vl{
		bool ex_eve=false;
		if((X+Bcnt)%2)ex_eve=true,--X;

		X=(X-Bcnt)/2; // 1個プラスx*2個
		ll div=X/Bcnt;
		ll rem=X%Bcnt;

		vl ans;
		rep(i,rem)ans.eb(div+1);
		rep(i,rem,Bcnt)ans.eb(div);
		each(a,ans)a=a*2+1;
		if(ex_eve)++ans.back();
		return ans;
	};
	ins(S);
	ll N=S.size();
	ll M=26;
	vp cnta(M);
	each(c,S)++cnta[c-'a'].fi;
	rep(i,M)cnta[i].se=i;
	sort(all(cnta)); reverse(all(cnta));

	if(cnta[0].fi<=(N+1)/2){
		vl ord;
		rep(i,0,N,2)ord.eb(i);
		rep(i,1,N,2)ord.eb(i);

		string ans; rep(i,N)ans+='.';
		ll cur=0;
		each2(cnt,a,cnta){
			rep(cnt)ans[ord[cur++]]=a+'a';
		}
		die(ans);
	}

	auto lens=part(cnta[0].fi,N-cnta[0].fi+1);
	queue<char> q;
	rep(i,N)if(S[i]!=cnta[0].se+'a')q.push(S[i]);
	/* out(lens); */

	string ans;
	rep(i,lens.size()){
		rep(lens[i])ans+=cnta[0].se+'a';
		if(i<lens.size()-1){
			ans+=q.front();
			q.pop();
		}
	}
	out(ans);
}
void yamada::solve() { inl(T); while(T--)tc(); }
