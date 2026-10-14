#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	const ll log=30;
	inl(N);
	vl A(N); in(A);
	vl cnt(log);
	rep(i,N)rep(t,log)if(A[i]>>t&1)++cnt[t];

	repr(t,log)if(cnt[t]>0){
		if(cnt[t]%2==0)die("Alice");
	}
	rep(t,log)if(cnt[t]>0){
		die(cnt[t]%2? "Bob":"Alice");
	}
}

void yamada::solve()
{
	inl(TC);
	while(TC--)tc();
}
