#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	ins(S);
	ll K=26;
	string T="PAKENCAMP";
	vl cnt(K),dnt(K);
	each(c,S)++cnt[c-'A'];
	each(c,T)++dnt[c-'A'];

	ll ans=0;
	rep(i,K){
		if(dnt[i]==0 && cnt[i]>0)die(-1);
		if(dnt[i]>0)amax(ans,(cnt[i]+dnt[i]-1)/dnt[i]);
	}
	out(ans);
}
