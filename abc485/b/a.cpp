#include "../../template/template.hpp"

void yamada::solve()
{
	IN(H,W,S=STR*H);
	rep(2){
		S=Transpose(S);
		each(i,s,S|Enumerate){
			if(All(s,[&](auto c){return c=='x';}))DIE(_?"Faucet":"Drain",i+1);
		}
	}
}
