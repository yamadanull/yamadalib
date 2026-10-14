#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	int T = 1;
	/* cout << T << "\n"; */
	while (T--) {
		ll N=randint(2,10);
		vl A(N);
		each(a,A)a=randint(1,10);

		out(N);
		out(A);
	}
}
