#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	vl A(N),B(N); in(A,B);
	sort(all(A)); sort(all(B));

	// [0,x)がM以上にならない
	auto check=[&](ll x)->bool{
		rep(i,x)if(A[i]+B[x-i-1]>=M)return false;
		return true;
	};

	ll ans=bisect<ll>(0,N+1,check)-1;
	ll bns=Sum(A)+Sum(B);
	bns-=M*(N-ans);
	out(bns);
}

void yamada::solve() { inl(TC); while(TC--)tc(); }
