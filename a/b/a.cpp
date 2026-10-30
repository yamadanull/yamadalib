#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N);
	ll ans=0;
	each(c,d,Zip(STR(),STR())){
		if(c=='o'||d=='o')++ans;
	}
	out(ans%2);
}
