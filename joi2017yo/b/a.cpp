#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M);
	vl A;
	rep(i,M){
		inl(a,b);
		A.eb(max(0LL,N-a));
	}
	sort(all(A));
	A.pop_back();
	out(Sum(A));
}
