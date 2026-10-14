#include "../../template/template.hpp"
#include "../../dp/inversion-counting.hpp"

void yamada::solve()
{
	inl(N,L);
	vl A(L);
	rep(i,L)A[i]=i;
	map<vl,ll> mp;
	vvl B;
	do{
		mp[A]=B.size();
		B.eb(A);
	}while(nxp(A));
	rep(i,L)A[i]=i;

	out("B.size():",B.size());
	ll maxdist=-infLL;
	rep(i,B.size()){
		amax(maxdist,swap_distance(A,B[i]));
	}
	out("maxdist:",maxdist);
}
