#include "../../template/template.hpp"
using namespace yamada;

ll f0(vvl A){
	ll N=A.size();
	auto dp=A;
	ll ans=0;
	rep(i,N)rep(j,N){
		if(i>0)dp[i][j]+=dp[i-1][j];
		if(j>0)dp[i][j]+=dp[i][j-1];
		if(A[i][j])ans+=dp[i][j]-1;
	}
	return ans;
}

ll f1(vvl A){
	each(v,A)each(a,v)a^=1;
	return f0(A);
}

void yamada::solve()
{
	inl(N);
	auto idx=[&](ll i,ll j){return i*N+j;};
	ll cnt=0;
	/* rep(msk,1LL<<(N*N-1)){ */
	/* 	vv(ll,A,N,N); */
	/* 	rep(id,N*N)if(msk>>id&1)A[id/N][id%N]=1; */

	/* 	ll ans=f0(A); */
	/* 	ll bns=f1(A); */
	/* 	if(ans==bns){ */
	/* 		if(++cnt%1000==0)out("cnt:",cnt),cout.flush(); */
	/* 		auto B=A; */
	/* 		B=Rotate(B,1); */
	/* 		B=Transpose(B); */
	/* 		B=Rotate(B,0); */
	/* 		if(A==B){ */
	/* 			out(); */
	/* 			out(ans); */
	/* 			vs S(N); */
	/* 			rep(i,N)rep(j,N)S[i]+=(A[i][j]? '#':'.'); */
	/* 			each(s,S)out(s); */
	/* 			cout.flush(); */
	/* 		} */
	/* 	} */
	/* } */

	rep(msk,1LL<<(N*2-2)){
		vv(ll,A,N,N);
		rep(i,N)rep(j,N)if(msk>>(i+j)&1)A[i][j]=1;
		A=Rotate(A);
		ll ans=f0(A);
		ll bns=f1(A);
		if(ans==bns){
			if(++cnt%1000==0)out("cnt:",cnt),cout.flush();
			out();
			out(ans);
			vs S(N);
			rep(i,N)rep(j,N)S[i]+=(A[i][j]? '#':'.');
			each(s,S)out(s);
			cout.flush();
		}
	}
}
