#include "../../template/template.hpp"

void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(N,K);
		auto check=[&](ll x)->bool{
			vl A(N);
			A[0]=x;
			ll k=K;
			rep(i,N-1){
				if(k>=A[i]-1){
					k-=A[i]-1;
					A[i+1]=A[i]*2-1;
				}
				else{
					A[i+1]=A[i]+k;
					k=0;
				}
			}
			return k>0;
		};

		ll x=bisect(2LL,(ll)inf,check);
		vl A(N); A[0]=x;
		rep(i,N-1){
			if(K>=A[i]-1){
				K-=A[i]-1;
				A[i+1]=A[i]*2-1;
			}
			else{
				A[i+1]=A[i]+K;
				K=0;
			}
		}
		out(A);
	}
}
