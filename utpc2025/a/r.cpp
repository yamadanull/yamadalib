#include "../../template/template.hpp"
#include "../../string/z-algorithm.hpp"
#include "../../misc/all.hpp"
using namespace yamada;

// BはAに含まれる？
bool check(vl &A,vl &B){
	ll N=A.size();
	ll M=B.size();
	auto BA=B;
	each(a,A)BA.eb(a);
	auto za=z_algorithm(BA);

	rep(i,N-M+1){
		if(za[i+M]>=M)return 1;
	}
	return 0;
}

void yamada::solve()
{
	out(1);
	while(1){
		ll N=randint(1,100);
		ll M=randint(N,100);
		ll K=randint(M,100);
		vl A(N),B(M),C(K);
		each(a,A)a=randint(0,K)+1;
		each(b,B)b=randint(0,K)+1;
		each(c,C)c=randint(0,K)+1;

		/* { */
		/* 	vl cnt(K),dnt(K); */
		/* 	each(c,C)++cnt[c-1]; */
		/* 	bool fn=1; */
		/* 	rep(2){ */
		/* 		swap(A,B); */
		/* 		each(a,A)++dnt[a-1]; */
		/* 		rep(i,K)if(dnt[i]>cnt[i])fn=0; */
		/* 	} */
		/* 	if(!fn)continue; */
		/* } */

		out(N,M,K);
		out(A);
		out(B);
		out(C);
		return;

		/* auto AB=A,BA=B; */
		/* each(b,B)AB.eb(b); */
		/* each(a,A)BA.eb(a); */
		/* if(A<B && AB>BA){ */
		/* 	rep(i,N)if(A[i]!=B[i]){ */
		/* 		out(N,M,K); */
		/* 		out(A); out(B); out(C); */
		/* 		return; */
		/* 	} */
		/* } */
	}
}
