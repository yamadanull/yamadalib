#include "../../template/template.hpp"
using namespace yamada;

ll cal(vs S,ll K){
	ll H=S.size();
	ll W=S[0].size();

	ll ans=0;
	rep(i,H){
		vl A(W);
		rep(j,W)if(S[i][j]=='#')A[j]=1;
		CumulativeSum cum(A);
		rep(l,W-K+1){
			ll r=l+K;
			if(cum.query(l,r)==0)++ans;
		}
	}
	return ans;
}

void yamada::solve()
{
	inl(H,W,K);
	vs S(H); in(S);

	ll ans=0;
	rep(2){
		swap(H,W);
		S=Transpose(S);
		ans+=cal(S,K);
	}
	out(ans);
}
