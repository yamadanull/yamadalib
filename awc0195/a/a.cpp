#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N);
	rep(N){
		IN(A,B);
		out(max(0LL,A-B));
	}
}
