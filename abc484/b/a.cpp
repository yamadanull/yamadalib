#include "../../template/template.hpp"

void yamada::solve()
{
	IN(K,A=LL*K);
	if(Max(A)!=9)DIE(-1);
	out(Min(A));
}
