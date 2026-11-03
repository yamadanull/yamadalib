#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	ll K=3;
	IN(A=LL*3);
	ll N=Sum(A);
	string T="PRS";
	string ans;
	ll mx=MaxElement(A)-A.begin();
	rep(N)ans+=T[mx];
	out(ans);
}
