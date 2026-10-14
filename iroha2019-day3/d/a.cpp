#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N);
	vs S(N); in(S);
	ll R=1,C=1;
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	string T="ULDR";

	ll Q=1000;
	while(Q--){
		/* out(Q); cout.flush(); */
		ll r=-1,c=-1;
		if(Q<1000-1){
			in(r,c);
			if(r>=1)--r; --c;
		}

		if(r<=-2)return;
		else if(r==-1){
			out("-"); cout.flush();
		}
		else{
			rep(x,4){
				ll I=R+di[x];
				ll J=C+dj[x];
				if(S[I][J]=='#')continue;
				if(abs(r-R)+abs(c-C)>abs(r-I)+abs(c-J))continue;
				out(T[x]); cout.flush();
				R=I;
				C=J;
				break;
			}
		}
	}
}
