#include "../../template/multitest-template.hpp"
#include "../../enumerate/sequences.hpp"
using namespace yamada;

map<vc<int>,ll> memo;
bool naive(vc<int> A){
	if(memo.count(A))return memo[A];
	each(i,a,A|enumerate){
		ll lim=a;
		if(i>0)amin(lim,A[i]-A[i-1]);
		rep(red,1,lim+1){
			auto B=A;
			B[i]-=red;
			if(i>0 && B[i-1]>B[i])continue;
			if(!naive(B))return memo[A]=1;
		}
	}
	return memo[A]=0;
}

bool cal(vc<int> A){
	ll N=len(A);
	ll ans=0;
	repr(i,1,N)A[i]-=A[i-1];
	ll nim=0;
	each(a,A|drop(1-N%2)|stride(2))nim^=a;
	return nim;
}

void exper(){
	inl(N,M);
	/* auto F=[&](auto A){ */
	/* 	auto ans=naive(A); */
	/* 	auto bns=cal(A); */
	/* 	auto B=A; */
	/* 	repr(i,1,N)B[i]-=B[i-1]; */
	/* 	/1* if(ans!=bns)err(B,ans); *1/ */
	/* 	err(B,ans); */
	/* }; */
	/* LengthFixedSequences(N,false,0,M+1,F); */
	each(A,product(vc<int>(N,M))){
		auto B=A;
		rep(i,1,N)B[i]+=B[i-1];
		auto ans=naive(B);
		auto bns=cal(B);
		if(ans!=bns){
			err(A);
		}
	}
}

void yamada::solve()
{
	/* exper(); */
	inl(N);
	vc<int> A(N); in(A);
	out(cal(A)?"Alice":"Bob");
}
