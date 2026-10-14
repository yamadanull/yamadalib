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
	ll ccofL=0;
	ll ccofR=infLL;

	rep(i,1,N+1){
		if(C[i]<0){
			if(B[i]<0)die(-1);
			amin(ccofR,B[i]/(-C[i]));
		}
		if(C[i]>0){
			if(B[i]<0){
				ll c=Ceil(-B[i],C[i]);
				amax(ccofL,c);
			}
		}
		if(C[i]==0 && B[i]<0)die(-1);
	}
	if(ccofL>ccofR)die(-1);

	ll csm=Sum(C);
	ll ans=0;
	rep(i,1,N+1)ans+=B[i];
	if(csm<0)ans+=csm*ccofR;
	else ans+=csm*ccofL;
	out(ans);
}
