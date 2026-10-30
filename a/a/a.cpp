#include "../../template/template.hpp"
#include "../../misc/rng.hpp"

void yamada::solve()
{
	IN(N);
	out(!!randint(0,N+1));
}
