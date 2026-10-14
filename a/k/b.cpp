#include "../../template/template.hpp"
#include "../../geometry/integer-geometry.hpp"
using namespace yamada;

using Line=pr<Point,Point>; // 昇順縛り
using Lines=vc<Line>;
Point INF(10000,10000);

bool online(Line l,Point p){
	if(cross(l.se-p,l.fi-p))return 0;
	return l.fi<=p && l.se<=p;
}

Lines inter(Line l,Line m){
	ll c=cross(l.se-l.fi,m.se-m.fi);
	ll d=cross(l.se-l.fi,l.se-m.fi);

	if(c==0 && d==0){
		auto ans=max(l.fi,m.fi);
		auto bns=min(l.se,m.se);
		if(ans<=bns)return{Lines{ans,bns}};
		return{};
	}
	if(c==0)return{};
	auto ans=m.fi+(m.se-m.fi)*d/c;
	if(online(l,ans) && online(m,ans))return{Lines{ans,ans}};
	return{};
}

Lines Hlines(Point A,Point B){
	if(A>B)swap(A,B);
	auto C=(A+B)/2;
	ll d=max(abs(C.x-A.x),abs(C.y-A.y));
	Points dr;
	dr.eb(-d,-d);
	dr.eb(+d,-d);
	dr.eb(+d,+d);
	dr.eb(-d,+d);

	auto ans0=INF;
	auto bns0=-INF;
	rep(di,4)rep(dj,4){
		Line dl={A+dr[di],A+dr[(di+1)%4]};
		Line dr={A+dr[dj],A+dr[(dj+1)%4]};
		each2(p,q,inter(dl,dr)){
			amin(ans0,p); amin(ans0,q);
			amax(bns0,p); amax(bns0,q);
		}
	}
	Lines ans;
	if(A.y<B.y){
		ans.eb(ans0-INF,ans0);
		ans.eb(ans0,bns0);
	}
	return ans;
}

vc<pr<Point,Point>> cal(Points P){
}

void yamada::solve()
{
	ll N=3;
	Points P(N);
	in(P);
	each(p,P){
		p=Point(p.x+p.y,p.x-p.y);
		p*=4;
	}
	each(p,P){
	}
}
