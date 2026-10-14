#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	ll N=randint(1,6);
	vp xy(N);
	FOR_E(x,y,xy){
		x=randint(0,5);
		y=randint(0,5);
	}

	OUT(N);
	FOR_E(x,y,xy)OUT(x,y);
}
