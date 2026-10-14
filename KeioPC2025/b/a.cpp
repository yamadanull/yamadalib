#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,K);
	vl A(N); in(A);
	auto B=mkrui(A);
	ll ans=Sum(B);
	rep(i,N)A[i]*=N-i;
	sort(all(A)); reverse(all(A));
	rep(i,K)ans-=A[i];
	out(ans);
}
