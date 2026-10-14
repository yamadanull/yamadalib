#include "../../template/template.hpp"
#include "../../atcoder/maxflow.hpp"
/* #include "../../flow/network-simplex.hpp" */
#include "../../flow/primal-dual.hpp"
using namespace yamada;

/* void exper(){ */
/* 	LL(N,K,L,R); */
/* 	vl A(N); IN(A); */
/* 	LL(X,Y,Z); */

/* 	auto S=0; */
/* 	auto v0=Iota(1,4)|rtov; */
/* 	auto v1=Iota(4,4+X+Y+Z)|rtov; */
/* 	auto v2=Iota(4+X+Y+Z,4+X+Y+Z+N)|rtov; */
/* 	auto T=4+X+Y+Z+N; */
/* 	atcoder::mf_graph<i128> g(T+1); */
/* 	ERR(S); */
/* 	ERR(v0); */
/* 	ERR(v1); */
/* 	ERR(v2); */
/* 	ERR(T); */

/* 	FOR(i,3)g.add_edge(S,v0[i],R); */
/* 	FOR(i,X)g.add_edge(v0[0],i,1); */
/* 	FOR(i,X,X+Y)g.add_edge(v0[1],i,1); */
/* 	FOR(i,X+Y,X+Y+Z)g.add_edge(v0[2],i,1); */

/* 	FOR(i,X+Y+Z){ */
/* 		LL(d,f); */
/* 		FOR(j,N){ */
/* 			if(abs(d-A[j])<=K){ */
/* 				g.add_edge(v1[i],v2[j],1); */
/* 			} */
/* 		} */
/* 	} */
/* 	FOR(i,N)g.add_edge(v2[i],S,1); */

/* 	auto f=g.flow(S,T); */
/* 	ERR(f); */
/* 	FOR_E(e,g.edges()){ */
/* 		ERR(e.from,e.to,e.cap,e.flow); */
/* 	} */
/* } */

void yamada::solve()
{
	LL(N,K,L,R);
	vl A(N); IN(A);
	LL(X,Y,Z);

	MaxGainFlow<i128,i128> g;
	auto S=g.add_vertex();
	auto v0=g.add_vertices(3);
	auto v1=g.add_vertices(X+Y+Z);
	auto v2=g.add_vertices(N);
	auto T=g.add_vertex();
	ERR(S);
	ERR(v0);
	ERR(v1);
	ERR(v2);
	g.add_sup(S,N);
	g.add_dem(T,N);

	FOR(i,3)g.add_edge(S,v0[i],L,R,0);
	FOR(i,X)g.add_edge(v0[0],v1[i],1,0);
	FOR(i,X,X+Y)g.add_edge(v0[1],v1[i],1,0);
	FOR(i,X+Y,X+Y+Z)g.add_edge(v0[2],v1[i],1,0);

	FOR(i,X+Y+Z){
		LL(d,f);
		FOR(j,N){
			if(abs(d-A[j])<=K){
				g.add_edge(v1[i],v2[j],1,f);
			}
		}
	}
	FOR(i,N)g.add_edge(v2[i],T,1,0);

	auto[fn,cost]=g.solve();
	if(!fn)OUT(-1);
	else OUT(cost);
}
