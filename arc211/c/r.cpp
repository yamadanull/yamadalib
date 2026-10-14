#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=10;

	string S;
	while(1){
		string T;
		rep(i,N)T+=(randint(0,2)? '#':'.');

		vp lr;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && T[l]==T[r])++r;
			if(l>0 || T[l]=='.')lr.eb(l,r);
		}
		if(lr.size()%2==0)lr.pop_back();

		if(lr.size()>=3){
			S=T;
			break;
		}
	}
	vl A(N);
	each(a,A)a=randint(1,3);

	out(N);
	out(S);
	out(A);
}
