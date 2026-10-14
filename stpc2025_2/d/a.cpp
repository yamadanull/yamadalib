#include "../../template/template.hpp"

void yamada::solve()
{
	auto check=[&](vl B)->bool{
		sort(all(B));
		return B[0]+B[1]>B[2];
	};
	inl(TC);
	while(TC--)
	{
		vl A(4); in(A);
		bool ans=false;
		rep(i,4){
			vl B;
			B.eb(A[i]+A[(i+1)%4]);
			rep(j,4)if(i!=j && (i+1)%4!=j)B.eb(A[j]);
			if(check(B))ans=true;
		}
		YesNo(ans);
	}
}
