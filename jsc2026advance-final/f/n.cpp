#include "../../template/template.hpp"
#include "../../multiplicative-function/divisor-multiple-transform.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N+1);
	rep(i,1,N+1)in(A[i]);

	auto B=A;
	{
		ll mx=Max(A);
		each(b,B)b=mx-b;
		multiple_transform::mobius_transform(B);
	}
	vl C(N+1,1); C[0]=0;
	multiple_transform::mobius_transform(C);
	out("C:",C);

	ll ans=0;
	rep(i,1,N+1){
		if(B[i]<0)die(-1);
		ans+=B[i];
	}
	out(ans);
}
