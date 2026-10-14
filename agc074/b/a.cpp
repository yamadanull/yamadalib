#include "../../template/template.hpp"
#include "../../dp/inversion-counting.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	if(Sum(A)!=Sum(B))die("No");
	if(inversion_counting(A) != inversion_counting(B))die("No");
	out("Yes");

	V<tuple<ll,ll,ll,ll>> ans;
	rep(i,N){
		if(A[i]==B[i])continue;
	}

	out(ans.size());
	for(auto&[a,b,c,d]:ans)out(a,b,c,d);
}
void yamada::solve() { inl(T); while(T--)tc(); }
