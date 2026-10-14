#include "../../template/template.hpp"

void yamada::solve()
{
	const ll M=2e5;
	inl(N,Q);
	ins(S);

	vs T(M);
	while(Q--){
		inl(op);
		if(op==1){
			inl(k,l,r); --k; --l;
			T[k]+=S.substr(l,r-l);
		}
		else{
			inl(I,J); --I; --J;
			if(T[I]<T[J])out("<");
			else if(T[I]==T[J])out("=");
			else out(">");
		}
	}
}
