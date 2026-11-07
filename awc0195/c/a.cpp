#include "../../template/template.hpp"

void yamada::solve()
{
	IN(H,W,S=STR*H,Q);
	VV(bool,A,H,W);
	rep(i,H)rep(j,W)A[i][j]=S[i][j]=='1';
	vl DIJ{0,-1,0,1,0};
	while(Q--){
		IN(r,c); --r; --c;
		A[r][c]=!A[r][c];
		each(di,dj,DIJ|Adjacent<2>){
			ll i=r+di;
			ll j=c+dj;
			if(inLR(0,i,H)&&inLR(0,j,W))A[i][j]=!A[i][j];
		}
	}

	rep(i,H)rep(j,W)S[i][j]=A[i][j]?'1':'0';
	each(s,S)out(s);
}
