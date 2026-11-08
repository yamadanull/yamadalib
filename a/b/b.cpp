#include "../../template/multitest-template.hpp"
#include "../../modint/montgomery-modint.hpp"

using mint = LazyMontgomeryModInt<998244353>;
void yamada::solve()
{
	IN(M);
	ll N=M*3+10;
	vl A(N);
	rep(M)A[LL()]=1;
	mint ans=M*(M-1)/2+M;
	/* err(ans); */

	CumulativeSum cum(A);
	rep(m,3){
		auto B=A;
		rep(i,m,N,3)B[i]=1;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N&&B[l]==B[r])++r;
			if(!B[l])continue;
			rep(i,l,r)if(A[i]&&i%3!=m){
				ll rL=i+3;
				amin(rL,r);
				ans+=cum(rL,r);
				err(m,l,i,r,ans);
			}
		}
		/* err(m,ans); */
	}
	rep(i,N-3)if(A[i]&&A[i+1]&&A[i+2]){
		ans+=1;
	}
	out(ans);
}
