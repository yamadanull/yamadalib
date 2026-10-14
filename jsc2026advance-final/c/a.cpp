#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M);
	vl A(N); in(A); each(a,A)--a;
	vl B(M); in(B); each(b,B)--b;
	vb vis(N);
	vl ans; // reved
	repr(i,M){
		if(vis[B[i]])continue;
		vis[B[i]]=1;
		ans.eb(B[i]);
	}
	repr(i,N){
		if(vis[A[i]])continue;
		vis[A[i]]=1;
		ans.eb(A[i]);
	}

	reverse(all(ans));
	each(a,ans)++a;
	out(ans);
}
