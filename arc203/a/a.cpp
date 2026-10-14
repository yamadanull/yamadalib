#include "../../template/template.hpp"

void yamada::solve()
{
	inl(TC);
	while(TC--)
	{
		inl(N,M);
		if(M%2==0){
			out(M/2*N);
		}
		else{
			out(M/2*N+1);
		}
	}
}
