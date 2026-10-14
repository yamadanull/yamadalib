#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	inl(N);
	vl A(N),B(N); in(A,B);
	reveres(all(B));
	each(b,B)--b;
}
