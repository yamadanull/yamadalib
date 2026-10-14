#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	int T = 1;
	cout << T << "\n";
	for (int _ = T; _--;) {
		vl A(3);
		each(a,A)a=randint(0,10);
		out(A);
	}
}
