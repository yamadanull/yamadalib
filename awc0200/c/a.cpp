#include "../../template/template.hpp"

void yamada::solve()
{
	IN(H,W,S=STR*H);
	ll i=0,j=0;
	while(1){
		ll I=i,J=j;
		if(S[i][j]=='v'){
			I++;
		}
		else{
			J++;
		}
		if(!inLR(0,I,H))DIE(i+1,j+1);
		if(!inLR(0,J,W))DIE(i+1,j+1);
		i=I;
		j=J;
	}
}
