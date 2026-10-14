#include "../../template/template.hpp"
#include "../../math/bigint-all.hpp"
#include "../../misc/sequences.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	auto As=LengthFixedSequences(N,true,1,M+1);
	each(A,As){
		bigint nume(0);
		bigint deno(1);
		rep(i,N){
			ll l=lcm(A[i],A[(i+1)%N]);
			nume*=l;
			nume+=deno;
			deno*=l;
		}
		if(nume>=deno){
			out("nume:",nume);
			out("deno:",deno);
			out(A);
			cout.flush();
		}
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
