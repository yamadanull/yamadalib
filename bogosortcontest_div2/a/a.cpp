#include "../../template/template.hpp"

void yamada::solve()
{
	IN(N);
	while(1){
		IN(P=--INT*N);
		bool ans=1;
		each(a,b,P|Adjacent<2>)if(a>b)ans=0;
		if(ans){
			fout("ok");
			return;
		}
		fout("shuffle");
	}
}
