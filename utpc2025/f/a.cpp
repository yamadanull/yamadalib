#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	inl(N,Q);
	ins(S);
	vl A(N);
	rep(i,N){
		if(S[i]=='(')A[i]=1;
		else A[i]=-1;
	}

	CumulativeSum cum(A);
	while(Q--){
		inl(l,r); --l;
		out(cum.query(l,r)==0? "Infinite":"Finite");
	}
}
