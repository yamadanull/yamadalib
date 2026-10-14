#include "../../template/multitest-template.hpp"
#include "../../dp/inversion-counting.hpp"

void yamada::solve()
{
	inl(N,K);
	vl A(N); in(A);
	bool fn=0;
	vvl B(K);
	each(k,b,B|vw::enumerate){
		rep(i,k,N,K)b.eb(A[i]);
	}

	auto toA=[&](vvl B)->vl{
		vl ans(N);
		rep(i,N)ans[i]=B[i%K][i/K];
		return ans;
	};

	rep(p,2){
		auto C=B;
		each(b,B){
			bool q=inversion_counting(b)%2;
			rg::sort(b);
			if(p!=q && mkuni(b).size()==b.size()){
				ll n=b.size();
				swap(b[n-2],b[n-1]);
			}
		}
		amin(A,toA(B));
		B=C;
	}

	out(A);
}
