#include "../../template/multitest-template.hpp"
using namespace yamada;

ll F(vint A){
	ll N=len(A);
	ll ans=0;
	FOR(l,N)FOR(r,l+1,N+1){
		ll x=0;
		FOR(i,l,r)x^=A[i];
		if(x==0)ans++;
	}
	return ans;
}

ll beauty(vint A){
	ll N=len(A);
	ll ans=N;
	ans-=F(A);
	return ans;
}

void exper(){
	LL(N);
	bool first=1;
	Product(vint(N,N),[&](auto A){
		FOR_E(a,A)++a;
		if(F(A)==0){
			if(first){
				ERR(A);
				vint B(N+1);
				FOR(i,N)B[i+1]=A[i]^B[i];
				ERR(B);
			}
			first=0;
		}
	});
}

void yamada::solve()
{
	exper();
}
