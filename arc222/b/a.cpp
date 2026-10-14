#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	vl A(3); in(A); reverse(all(A));
	{
		ll mxi=-1;
		rep(i,3)if(Max(A)==A[i])mxi=i;
		rotate(A.begin(),A.begin()+mxi,A.end());
	}

	rep(i,1,3)if(A[0]==A[i] && A[3-i]==0){
		die(A[0]);
	}

	ll ans=0;
	if(A[0]<A[1]+A[2]){
		// 勝つ（少ない方）(2)
		ll cnt=A[1]+A[2]-A[0];
		cnt=(cnt-1)/2;
		amin(cnt,A[2]);
		amin(cnt,A[1]-1);
		if(cnt>0){
			A[1]-=cnt+1;
			A[2]-=cnt;
			ans+=cnt;
		}
	}

	if(A[2]>=1){
		ll red=A[2]-1;
		A[0]-=red;
		A[2]=0;
		ans+=red;
		assert(A[0]>=0);
	}

	if(A[0]>=2 && A[1]>=1){
		ll red=min(A[0],A[1]+1);
		A[0]-=red;
		A[1]-=red-1;
		ans+=red-1;
	}
	out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
