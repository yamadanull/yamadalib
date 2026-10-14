#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	ll mn=Min(A);
	ll mx=Max(A);
	each(a,A){
		out(max(mx-a,a-mn));
	}
}
