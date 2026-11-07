#include "../../template/template.hpp"
#include "../../tree/tree-query.hpp"
using namespace yamada;

void cal1(){
	IN(N,S=STR);
	if(Count(S,'0')==N-1){
		out(N);
		rep(i,N-1)out(i+1,i+2);
		out(1,3);
		return;
	}
	out(N-1);
	ll U=-1;
	rep(i,N-1)if(S[i]=='1'){
		out(N,i+1);
		U=i;
	}
	rep(i,N-1)if(S[i]=='0'){
		out(U+1,i+1);
	}
}

void cal2(){
	IN(N,M);
	auto g=graph(N,M);
	string ans;
	if(N<=M){
		rep(N-1)ans+='0';
		DIE(ans);
	}
	Tree tree(g,N-1);
	rep(i,N-1){
		err(i,tree.depth(i));
		ans+=tree.depth(i)%2+'0';
	}
	out(ans);
}

void yamada::solve()
{
	IN(S=STR,T);
	while(T--){
		S[0]=='f'?cal1():cal2();
	}
}
