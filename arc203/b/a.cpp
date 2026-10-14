#include "../../template/template.hpp"

void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(N);
		vl A(N),B(N); in(A,B);
		if(Sum(A)!=Sum(B)){
			out("No");
			continue;
		}
		if(Sum(A)>=2){
			out("Yes");
			continue;
		}
		if(A==B){
			out("Yes");
			continue;
		}
		YesNo(A[0]!=1&&A[N-1]!=1&&B[0]!=1&&B[N-1]!=1);
	}
}
