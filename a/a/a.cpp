#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"
using namespace yamada;

bool check(vl A,vl B){
	ll N=len(A);
	addmax_lazyseg<ll> seg(A);
	rep(i,N){
		if(B[i]){
			seg.apply(i,N,1);
		}
		else{
			seg.apply(0,i+1,1);
		}
	}
	each(a,seg.get())if(a%2==0)return 0;
	return 1;
}

void yamada::solve()
{
	IN(N);
	vl A=STR()|Map([&](auto c)->ll{return c=='o';})|rtov;
	auto output=[&](vl B)->void{
		if(YesNo(!B.empty())){
			string ans;
			each(b,B)ans+=b?'R':'L';
			out(ans);
		}
	};
	auto B=A;
	each(b,B|Stride(2))b^=1;
	auto C=B;
	each(c,C)c^=1;
	if(check(A,B)){output(B);return;}
	if(check(A,C)){output(C);return;}
	out("No");
}
