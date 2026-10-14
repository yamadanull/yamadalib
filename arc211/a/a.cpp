#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	ll D=10;
	vl A(D);
	rep(i,1,D)in(A[i]);
	ll len=Sum(A);
	if(A[5]*2-1>=len)die((A[5]*2-1)-len);
	if(A[5])die(0);
	err(A);

	ll L=-infLL,R=infLL;
	rep(i,5)if(A[i])amax(L,i);
	rep(i,6,D)if(A[i])amin(R,i);
	if(R==infLL)die(0);
	if(L==-infLL)die(0);
	rep(i,L)if(A[i])die(0);
	rep(i,R+1,D)if(A[i])die(0);
	out(1);
}
void yamada::solve() { ini(T); while(T--)tc(); }

