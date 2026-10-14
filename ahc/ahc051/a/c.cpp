#include "../../template/template.hpp"
#include "../../graph/strongly-connected-components.hpp"
#include "../../graph/graph-template.hpp"
#include "../../misc/all.hpp"
#include "../../geometry/integer-geometry.hpp"
using namespace yamada;

const Point Start(0,5000);
int N,M,K;
Points ps;
VV<double> Ps;
vi ans,cns,d_idxs,s_idxs;
vvi to_d,to_s;
int bns;
UnweightedGraph g;
double score;
VV<double> dist;

#include "score.hpp"

int near_d(int pos){
	double x=rnd(-5,0);
	int rank=pow(2,x)*N;
	return to_d[pos][rank];
}

int near_s(int pos){
	double x=rnd(-5,0);
	int rank=pow(2,x)*M;
	return to_s[pos][rank];
}

bool inter_check(int a,int b,int c,int d){
	if(a==c||a==d||b==c||b==d)return true;
	Point p1=ps[a],p2=ps[b],q1=ps[c],q2=ps[d];
	if(cross(p2-p1,q1-p1)*cross(p2-p1,q2-p1)>0)return true;
	if(cross(q2-q1,p1-q1)*cross(q2-q1,p2-q1)>0)return true;
	return false;
}

bool add_e(){
	int pos=-1,b=-1;
	rep(i,N,N+M)if(!g[i].empty()){
		rep(j,2){
			if(inLR(0,g[i][j],N)){ pos=i; b=j; break; }
		}
		if(pos>=0)break;
	}
	if(pos<0)return false;
	rep(3){
		int i=randint(N,N+M);
		if(g[i].empty())continue;
		int j=randint(0,2);
		if(inLR(0,g[i][j],N)){ pos=i; b=j; break; }
	}

	int TIMELIMIT=0.03*CLOCKS_PER_SEC;
	int ti=clock();
	while(clock()-ti<TIMELIMIT){
		int to=near_s(pos);
		if(!g[to].empty())continue;
		if(pos==to)continue;
		int pto=g[pos][b];
		g[pos][b]=to;
		g[to].eb(near_d(to));
		g[to].eb(near_d(to));
		if(StronglyConnectedComponents(g).dag.size()<N+M){
			g[pos][b]=pto; g[to].clear(); continue;
		}

		bool fn=true;
		rep(i,N+M){
			each(e,g[i]){
				if(!inter_check(i,e,pos,to)){ fn=false; break; }
				if(!inter_check(i,e,to,g[to][0])){ fn=false; break; }
				if(!inter_check(i,e,to,g[to][1])){ fn=false; break; }
			}
			if(!fn)break;
		}
		if(!fn){ g[pos][b]=pto; g[to].clear(); continue; }
		cns[to-N]=randint(0,K);
		return true;
	}
	return false;
}

bool change_e(){
	int pos=-1,b=-1;
	rep(i,N,N+M)if(!g[i].empty()){
		rep(j,2){
			if(!inLR(0,g[i][j],N)){ pos=i; b=j; break; }
		}
		if(pos>=0)break;
	}
	if(pos<0)return false;
	rep(3){
		int i=randint(N,N+M);
		if(g[i].empty())continue;
		int j=randint(0,2);
		if(!inLR(0,g[i][j],N)){ pos=i; b=j; break; }
	}

	int TIMELIMIT=0.03*CLOCKS_PER_SEC;
	int ti=clock();
	while(clock()-ti<TIMELIMIT){
		int to=near_s(pos);
		if(g[to].empty())continue;
		if(to==g[pos][b])continue;
		if(pos==to)continue;
		int pto=g[pos][b];
		g[pos][b]=to;
		if(StronglyConnectedComponents(g).dag.size()<N+M){
			g[pos][b]=pto; continue;
		}

		bool fn=true;
		rep(i,N+M){
			each(e,g[i])if(!inter_check(i,e,pos,to)){ fn=false; break; }
			if(!fn)break;
		}
		if(!fn){ g[pos][b]=pto; continue; }
		return true;
	}
	return false;
}

void yamada::solve()
{
	const int ti=clock();
	in(N,M,K);
	ps.resize(N+M); in(ps);
	Ps.resize(K,V<double>(N)); in(Ps);

	d_idxs.resize(N); rep(i,N)d_idxs[i]=i;
	s_idxs.resize(M); rep(i,M)s_idxs[i]=i;
	sort(all(d_idxs),[&](int a,int b){return ps[a]<ps[b];});
	sort(all(s_idxs),[&](int a,int b){return ps[a+N]<ps[b+N];});

	dist.resize(N+M,V<double>(N+M));
	rep(i,N+M)rep(j,N+M){
		Point v=ps[i]-ps[j];
		dist[i][j]=sqrt(v.x*v.x+v.y*v.y);
	}

	to_d.resize(N+M,vi(N)); each(td,to_d)rep(i,N)td[i]=i;
	to_s.resize(N+M,vi(M)); each(ts,to_s)rep(i,M)ts[i]=i+N;
	rep(i,N+M){
		sort(all(to_d[i]),[&](int a,int b){return dist[i][a]<dist[i][b];});
		sort(all(to_s[i]),[&](int a,int b){return dist[i][a]<dist[i][b];});
	}

	ans.resize(N); rep(i,N)ans[i]=i;
	bns=s_idxs[0]+N;
	g.resize(N+M);
	cns.resize(M,-1);
	cns[bns-N]=randint(0,K);
	g[bns].eb(d_idxs[0]);
	g[bns].eb(d_idxs[1]);

	{ // add 分別機
		int TIMELIMIT=0.50*CLOCKS_PER_SEC;
		int cnt=0,dnt=0;
		while(clock()-ti<TIMELIMIT){
			if(!add_e()){
				if(++cnt%20==0)if(change_e())++dnt;
			}
			else cnt=0;
		}
		out(dnt);
	}

	ans_adj();
	{ // どの分別機を使うか調整
		int TIMELIMIT=1.80*CLOCKS_PER_SEC;
		int cnt=0;
		score=cal_score();
		while(clock()-ti<TIMELIMIT){
			int pos=randint(N,N+M);
			if(cns[pos-N]>=0){
				assert(g[pos].size()==2);
				int ocns=cns[pos-N];
				cns[pos-N]=randint(0,K);
				double nscore=cal_score();
				if(nscore>score)cns[pos-N]=ocns;
				else{
					score=nscore;
					if(++cnt%10==0)ans_adj();
				}
			}
		}
		/* out(cnt); */
	}

	out(ans);
	out(bns);
	rep(i,N,N+M){
		if(cns[i-N]<0)out(-1);
		else out(cns[i-N],g[i]);
	}
}
