#include "../../monoid/minidx.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../template/template.hpp"
 
void yamada::solve()
{
	IN(N,A=PR(LL,IDX)*N);
	SegmentTree<MONOID::MinIdx<ll>> seg(A);
	out(seg().se+1);
}
