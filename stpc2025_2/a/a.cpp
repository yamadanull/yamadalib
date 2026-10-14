#include "../../template/template.hpp"
#include "../../misc/random-graph.hpp"
using namespace yamada;

void tc()
{
	inl(N,K);
	if(N==1){
		if(YesNo(K==1));
		return;
	}
	if(N==2){
		if(YesNo(K==1))out(1,2);
		return;
	}
	if(N==3){
		if(YesNo(K==2)){ out(1,2); out(2,3); }
		return;
	}
	if(N==4){
		if(YesNo(K==2)){ out(1,2); out(2,3); out(3,4); }
		return;
	}
	if(K==1)die("No");
	if(N==K){
		if(N==5 || N==6)die("No");
		out("Yes");
		UnweightedGraph g(N);
		rep(i,N-4)g[i].eb(i+1);
		g[0].eb(N-3);
		g[0].eb(N-1);
		g[N-3].eb(N-2);
		print_edge(g);
		return;
	}
	if(K==3 && N%2){
		out("Yes");
		UnweightedGraph g(N);
		rep(i,1,N,2){
			g[0].eb(i);
			g[i].eb(i+1);
		}
		print_edge(g);
		return;
	}
	if(K==3 && N%2==0){
		out("Yes");
		UnweightedGraph g(N);
		rep(i,3)g[i].eb(i+1);
		rep(i,4,N,2)g[0].eb(i);
		rep(i,5,N,2)g[3].eb(i);
		print_edge(g);
		return;
	}

	out("Yes");
	UnweightedGraph g(N);
	rep(i,K-2)g[i].eb(i+1);
	rep(i,K-1,N)g[0].eb(i);
	print_edge(g);
}
void yamada::solve() { inl(T); while(T--)tc(); }
