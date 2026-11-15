#include "../../template/template.hpp"

void yamada::solve()
{
	set<vl>st;
	IN(N,A=LL*N);
	rep(l,N)rep(r,l+1,N+1){
		auto B=A;
		rotate(B.begin()+l,B.begin()+r-1,B.begin()+r);
		st.insert(B);
	}
	out(len(st));
}
