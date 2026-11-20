#include "../../template/template.hpp"
#include "../../segment-tree/lazy-segment-tree-utility.hpp"

void yamada::solve()
{
	IN(N,T,BIND(A,B)=~PR(--LL,LL)[N]);
	ll ans=0;
	rep(msk,1<<N){
		ll t=0;
		rep(i,N)if(msk>>i&1)t+=B[i];
