#include "../../template/multitest-template.hpp"

const int LG=10;
void yamada::solve()
{
	inl(A,B,C);
	auto ans=mkiota(A);
	auto bns=mkiota(B);
	each(a,ans)each(b,bns)if((a^b)==C)die("No");
	out("Yes");
	ans.eb(1<<LG);
	rep(i,C)bns.eb((1<<LG)+i);
	out(ans.size(),ans);
	out(bns.size(),bns);
}
