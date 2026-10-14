#include "../../template/template.hpp"
#include "../../enumerate/sequences.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
map<tuple<vc<int>,vc<int>,int>,mint> memo;
bool check(vc<int> A){
	int N=A.size();
	each(a,A)if(!inLR(0,a,N))return 0;
	vc<int> cnt(N);
	each(a,A)++cnt[a];
	return Min(cnt)==Max(cnt);
}
mint naive(vc<int> A,vc<int> B,int M){
	if(M==0)return check(A) && check(B);
	if(memo.count(mkt(A,B,M)))return memo[mkt(A,B,M)];

	int N=A.size();
	mint ans=0;
	rep(i,N)rep(j,i+1,N){
		swap(A[i],A[j]);
		ans+=naive(A,B,M-1)*2;
		swap(A[i],A[j]);
	}
	rep(i,N){
		swap(A[i],B[i]);
		ans+=naive(A,B,M-1);
		swap(A[i],B[i]);
	}
	return memo[mkt(A,B,M)]=ans;
}

void yamada::solve()
{
	inl(N,M);
	/* vc<int> A(N),B(N); in(A,B); each(a,A)--a; each(b,B)--b; */
	/* out(naive(A,B,M)); */
	auto F=[&](auto C){
		int n=C.size();
		auto A=mkiota(N);
		auto B=A;
		auto Crui=mkrui(C);
		rep(i,n){
			int l=Crui[i];
			int r=Crui[i+1];
			if(r-l>=1)rotate(A.begin()+l,A.begin()+l+1,A.begin()+r);
		}

		out(C,":",A,":",naive(A,B,M));
	};

	SumFixedSequences<true>(N,F);
}
