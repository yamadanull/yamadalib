#include "../../template/template.hpp"
#include "../../enumerate/sequences.hpp"
using namespace yamada;

bool cal(vc<int> A){
	bool ans=0;
	vc<int> res;
	ll N=A.size();
	auto F=[&](auto P){
		auto B=A;
		rep(i,N)B[i]=A[P[i]];
		bool bns=1;
		rep(i,N){
			ll cnt=0;
			rep(j,i){
				if(B[j]<B[i])++cnt;
			}
			if(cnt!=B[i]){
				bns=0;
				break;
			}
		}
		if(bns){
			res=B;
			ans=1;
		}
	};

	nxp(N,F);
	/* if(ans)out(res); */
	return ans;
}

void yamada::solve()
{
	inl(N);
	vc<int> A(N); in(A);
	YesNo(cal(A));
	/* auto F=[&](auto A){ */
	/* 	bool ans=cal(A); */
	/* 	out(A,":",cal(A)); */
	/* }; */

	/* LengthFixedSequences(N,false,0,N,F); */
}
