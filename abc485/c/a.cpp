#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	vl ans(N,infLL);
	for(ll l=0,r=0;l<N;l=r){
		while(r<N&&A[l]==A[r])++r;
		rep(i,l,r){
			if(r<N)amin(ans[i],r-i);
			if(l>0)amin(ans[i],i-l+1);
		}
	}
	out(ans);
}
