#include "../../template/template.hpp"
#include "../../geometry/line.hpp"

void yamada::solve()
{
	inl(N,M);
	Polygon S(N),T(M); in(S,T);

	Points inter;
	rep(i,N)rep(j,M){
		Line l(S[i],S[(i+1)%N]);
		Line m(T[j],T[(j+1)%M]);
		if(cross(l.b-l.a,m.a-l.a)*cross(l.b-l.a,m.b-l.a)>=0)continue;
		if(cross(m.b-m.a,l.a-m.a)*cross(m.b-m.a,l.b-m.a)>=0)continue;

		Point M=cross_point_ll(l,m);
		inter.eb(M);
	}

	each(p,S){
		if(contains_convex(T,p))inter.eb(p);
	}
	each(p,T){
		if(contains_convex(S,p))inter.eb(p);
	}

	Polygon ans=convex_hull(inter);
	out(area(ans));
}
