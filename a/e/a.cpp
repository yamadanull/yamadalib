#include "../../template/multitest-template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

vl cal_dp(ll M,vl A){ // Aの値をi(<M)回ずらしてorしたときのカウント
	ll N=len(A);
	vl nx(N,M);
	rep(i,N-1)amin(nx[i],A[i+1]-A[i]);
	Sort(nx);

	addmax_lazyseg<ll> seg(vl(M,0)); // i回目のずらして増える数
	rep(i,N){
		err(N,M,nx[i]);
		seg.apply(1,nx[i],1);
	}
	vl ans(M,N);
	rep(i,1,M)ans[i]=ans[i-1]+seg[i];
	err(ans);
	return ans;
}

vl cal(string S,string T){
	ll N=len(S);
	ll M=len(T);
	ll mxJ=-1;
	vl JS;
	rep(j,M)if(T[j]=='W'){
		mxJ=j;
		JS.eb(j);
	}

	auto dp=cal_dp(N,JS);

	vl ans;
	ll mxI=-1;
	each(i,c,S|Enumerate){
		if(c=='W'){
			mxI=i;
			continue;
		}

		if(mxI<0){ //koko
			ans.eb(dp[i]+1);
		}
		else if(mxJ<0){
			ans.eb(M+1);
		}
		else{
			ll mx=mxJ+i;
			amax(mx,mxI+M);
			err(mxI,mxJ);
			ans.eb(mx-mxI+1);
		}
	}
	return ans;
}

void yamada::solve()
{
	IN(N,M,S=STR,T=STR);
	out(cal(S,T));
	out(cal(T,S));
}
