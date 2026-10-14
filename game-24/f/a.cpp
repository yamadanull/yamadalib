#include "../../template/multitest-template.hpp"
using namespace yamada;

map<string,bool> memo;
bool naive(string S){
	if(memo.count(S))return memo[S];
	ll N=len(S);
	rep(i,N-1)if(S[i]!=S[i+1]){
		string T;
		T+=S.substr(0,i);
		T+=S.substr(i+2,N);
		if(!naive(T))return memo[S]=1;
	}
	return memo[S]=0;
}
void yamada::solve()
{
	inl(N);
	ins(S);
	each(c,S)c-='A';
	out(naive(S)?"Alice":"Bob");
}
