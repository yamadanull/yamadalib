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
	vl A(N); in(A);
	sort(all(A));
	bool ans=1;
	rep(i,N)if(A[i]>i)ans=0;

	vl cnt(N); rep(i,N)cnt[A[i]]++;

	if(YesNo(ans)){
		vl B;
		vl rem;
		rep(i,N){
			if(cnt[i]>0){
				B.eb(i);
				--cnt[i];
			}
			else{
				assert(!rem.empty());
				B.eb(rem.back());
				rem.pop_back();
			}
			while(cnt[i]--)rem.eb(i);
		}

		A=B;
		/* rep(i,N){ // del */
		/* 	ll cnt=0; */
		/* 	rep(j,i){ */
		/* 		if(A[j]<A[i])++cnt; */
		/* 	} */
		/* 	assert(cnt==A[i]); */
		/* } */
		out(A);
	}
}
