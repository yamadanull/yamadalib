#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	auto check=[](vl A)->bool{
		rep(i,A.size()-1){
			if(i%2==0 && A[i]>=A[i+1])return 0;
			if(i%2==1 && A[i]<=A[i+1])return 0;
		}
		return 1;
	};
	inl(N);
	vl A(N); in(A);
	CumulativeSum cum(A);

	ll ans=1;
	rep(msk,1<<(N-1)){
		vl sep{0};
		rep(i,N-1)if(msk>>i&1)sep.eb(i+1);
		sep.eb(N);

		vl B;
		each(l,r,sep|vw::adjacent<2>){
			B.eb(cum(l,r));
		}
		if(check(B))amax(ans,B.size());
	}
	out(N-ans);
}
