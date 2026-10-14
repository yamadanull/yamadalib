#include "../../template/multitest-template.hpp"
#include "../../enumerate/sequences.hpp"
#include "../../prime/prime-enumerate.hpp"
using namespace yamada;

auto ps=prime_enumerate(30);
map<vc<int>,ll> memo;
ll f(vc<int> A){
	if(Min(A)==Max(A))return A.front();
	ll ans=1;
	each(p,ps){
		auto B=A;
		each(b,B)if(b%p==0)b--;
		if(B==A)continue;
		amax(ans,f(B));
	}
	return memo[A]=ans;
}

void yamada::solve()
{
	inl(N);
	/* rep(i,1,N)rep(j,i+1,N){ */
	/* 	ll fij=f({i,j}); */
	/* 	if(fij<=i-2)fout(i,j,":",fij); */
	/* } */
	vc<int> A(N); in(A);
	sort(all(A));
	out(f(A));

	/* auto F=[&](auto A){ */
	/* 	ll fa=f(A); */
	/* 	if(fa<=A.front()-2){ */
	/* 		out("assert",A); */
	/* 	} */
	/* }; */
	/* LengthFixedSequences(N,false,2,N+1,F); */
}
