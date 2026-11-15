#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N,B=LL*N);
	if(A==B)DIE("Yes");
	ll aL=0,aR=N;
	while(aL<N && A[aL]==B[aL])++aL;
	while(aR>0 && A[aR-1]==B[aR-1])--aR;
	Rotate(A.begin()+aL,A.begin()+aL+1,A.begin()+aR);
	if(A==B)DIE("Yes");
	rep(2)Rotate(A.begin()+aL,A.begin()+aR-1,A.begin()+aR);
	YesNo(A==B);
}
