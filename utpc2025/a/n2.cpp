#include "../../template/template.hpp"
#include "../../string/z-algorithm.hpp"
using namespace yamada;

// BはAに含まれる？
bool check(vl &A,vl &B){
	ll N=A.size();
	ll M=B.size();
	auto BA=B;
	each(a,A)BA.eb(a);
	auto za=z_algorithm(BA);

	rep(i,N-M+1){
		if(za[i+M]>=M)return 1;
	}
	return 0;
}

void tc()
{
	inl(N,M,K);
	vl A(N),B(M),C(K); in(A,B,C);
	sort(all(C));

	do{
		if(check(C,A) && check(C,B))die(C);
	}while(nxp(C));
	out(-1);
}
void yamada::solve() { ini(T); while(T--)tc(); }
