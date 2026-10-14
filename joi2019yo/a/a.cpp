#include "../../template/template.hpp"

void yamada::solve()
{
	inl(a,b,c);
	ll cur=0;
	rep(i,infLL){
		if(i%7==6)cur+=b;
		cur+=a;
		if(cur>=c)die(i+1);
	}
}
