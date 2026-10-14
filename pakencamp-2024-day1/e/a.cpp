#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N); in(A);
	vp Ai;
	rep(i,N)Ai.eb(A[i],i);
	sort(all(Ai)); sort(all(A));

	inl(Q);
	while(Q--){
		inl(b);
		ll pos=bisect(0LL,N,[&](ll i){return A[i]<b;});
		if(pos==N)--pos;
		else if(pos>0){
			if(abs(A[pos]-b)==abs(A[pos-1]-b)){
				if(Ai[pos].se>Ai[pos-1].se)--pos;
			}
			else if(abs(A[pos]-b)>abs(A[pos-1]-b))--pos;
		}
		A[pos]=b;
		out(Ai[pos].se+1);
	}
}
