#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	const int K=26;
	IN(N,S=STR,Q);
	auto A=CT(0)[N][K](); rep(i,N)A[S[i]-'a'][i]++;

	vc<sum_segtree<ll>> segs;
	each(a,A)segs.eb(a);

	rep(Q){
		IN(T=STR);
		vl cnt(K); each(c,T)cnt[c-'a']++;
		ll ans=0;
		rep(c,K)if(cnt[c]){
			ll bns=segs[c].max_right(0,[&](ll sm){return sm<cnt[c];});
			err(c,bns);
			amax(ans,bns);
		}
		out(ans+1);
	}
}
