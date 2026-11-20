#include "../../template/template.hpp"

void yamada::solve()
{
	IN(H,W,S=STR*H);
	auto isCell=[&](ll i,ll j)->bool{
		if(!inLR(0,i,H))return 0;
		if(!inLR(0,j,W))return 0;
		return 1;
	};
	auto isFire=[&](ll i,ll j)->bool{
		if(!isCell(i,j))return 0;
		return S[i][j]=='#';
	};
	VVV(ll,dp,H,W,Power(3,W+1),-infLL);
	auto F=[&](ll state,ll i,ll j,bool fn)->pair<ll,ll>{
		auto A=Digit(state,3,W+1);
		auto pos=[&](ll t)->pair<ll,ll>{
			ll ans=i*W+j-t;
			return{floor(ans,W),modulo(ans,W)};
		};
		auto idx=[&](ll I,ll J)->ll{
			ll u=i*W+j;
			ll U=I*W+J;
			return u-U;
		};
		ll bns=0;
		auto add=[&](ll I,ll J){
			assert(isCell(I,J));
			if(A[idx(I,J)]==2)return;
			if(++A[idx(I,J)]==2)++bns;
		};
		ll here=0;
		if(fn){
			if(i>0&&j>0)add(i-1,j-1);
			if(i>0)add(i-1,j);
			if(i>0&&j<W-1)add(i-1,j+1);
			if(j>0)add(i,j-1);
