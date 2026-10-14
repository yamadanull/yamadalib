#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	vl B(N);
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && A[l]==A[r])++r;
		if(A[l]==0 && r-l>=2);
		else{
			rep(i,l,r)B[i]=1;
		}
	}

	inl(Q);
	while(Q--){
		inl(x); --x;
	}
}
