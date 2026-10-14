#include "../../template/multitest-template.hpp"
using namespace yamada;

void exper(){
	LL(N,K);
	vl L(N-1),R(N-1); ZIN(L,R);
	FOR_E(l,L)--l;
	FOR_E(r,R)--r;
	vs T(N-1);
	string S('L',N-1);
	FOR(30){
		ll u=0;
		while(u<N-1){
			if(S[u]=='L'){
				S[u]='R';
				u=R[u];
			}
			else{
				S[u]='L';
				u=L[u];
			}
		}
		FOR_E(c,t,Zip(S,T))t+=c;
	}
	FOR(u,N-1)ERR(u,T[u]);
}

void yamada::solve()
{
	exper();
}
