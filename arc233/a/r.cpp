#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	int T = 10000;
	cout << T << "\n";
	while (T--) {
		ll M=randint(4,200);

		vc<bool> fn(M);
		rep(i,1,(M+1)/2){
			fn[i]=randint(0,2);
			fn[M-i]=!fn[i];
		}
		if(M%2==0)fn[M/2]=1;
		vl S;
		each(i,f,fn|Enumerate)if(f)S.eb(i);
		assert(len(S)==M/2);

		out(M);
		out(S);
	}
}
