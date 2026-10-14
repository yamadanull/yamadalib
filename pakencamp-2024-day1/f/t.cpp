#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"

void yamada::solve()
{
	inl(N);
	YesNo(!is_prime(N));
}
