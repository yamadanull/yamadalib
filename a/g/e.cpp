#include "../../template/template.hpp"
using namespace yamada;

void exprm(ll N){
	vp IJ;
	rep(i,N)rep(j,N)IJ.eb(i,j);
	vl di{0,0,1,1};
	vl dj{0,1,0,1};
	auto F=[&](auto P){
		auto ij=p_shf(P,IJ,true);
		vv(ll,A,N,N);
		vv(ll,B,N,N);
		rep(i,N)rep(j,N)tie(A[i][j],B[i][j])=ij[i*N+j];
		rep(i,N-1)rep(j,N-1){
			ll cnt=0,dnt=0;
			rep(x,4){
				ll I=i+di[x];
				ll J=j+dj[x];
				cnt+=A[I][J];
				dnt+=B[I][J];
			}
			if(cnt!=dnt)return;
		}

		/* err(); */
		/* each(a,A)err(a); */
		/* each(b,A)err(b); */
		err(P);
	};
	nxp(N*N,F);
}

void yamada::solve()
{
	inl(N);
	vv(ll,A,N,N);
	vv(ll,B,N,N);
}
