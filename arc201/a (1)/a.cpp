#include "../../template/template.hpp"

void yamada::solve()
{
	inl(T);
	while(T--)
	{
		inl(N);
		ll x=0;
		ll y=0;
		// yをひとつ減らしてxをひとつ増やすという操作を何回出来る
		ll rem=0;
		rep(i,N){
			inl(a,b,c);
			if(b<=a && b<=c){
				y+=b;
				rem+=b;
			}
			else if(b<=c){ // a<b
				y+=b;
				rem+=a;
			}
			else if(b<=a){// c<b
				x+=b-c;
				y+=c;
				rem+=c;
			}
			else if(a+c>=b){ // ここから先はbが一番でかい
				x+=b-c;
				y+=c;
				rem+=min(c,a-(b-c)); // a-(b-c)=a+c-b>=0
			}
			else{ // a+c<b
				x+=a;
				y+=c;
			}
		}

		if(y<=x)out(y);
		else if(y-rem>=x+rem)out(x+rem);
		else out((x+y)/2);
	}
}
