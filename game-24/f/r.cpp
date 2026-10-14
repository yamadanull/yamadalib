#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	int T = 10;
	cout << T << "\n";
	for (int _ = T; _--;) {
		ll N=30;
		string S;
		rep(N)S+='A'+randint(0,3);
		out(N,S);
	}
}
