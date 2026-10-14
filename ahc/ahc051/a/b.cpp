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
vi ans,cns;
int bns;
vi d_idxs,s_idxs;
UnweightedGraph g;
double score;

#include "score.hpp"

bool inter_check(int a,int b,int c,int d){
	if(a==c||a==d||b==c||b==d)return true;
	Point p1=ps[a],p2=ps[b],q1=ps[c],q2=ps[d];
	if(cross(p2-p1,q1-p1)*cross(p2-p1,q2-p1)>0)return true;
	if(cross(q2-q1,p1-q1)*cross(q2-q1,p2-q1)>0)return true;
	return false;
}

bool add_e(int pos){
	rep(t,2){
		int TIMELIMIT=0.03*CLOCKS_PER_SEC;
		int ti=clock();
		while(clock()-ti<TIMELIMIT){
			int to=randint(0,N);
			bool fn=true;
			rep(i,N+M){
				each(e,g[i])if(!inter_check(i,e,pos,to)){ fn=false; break; }
				if(!fn)break;
			}
			if(fn){ g[pos].eb(to); break; }
		}
		if(g[pos].size()<=t){g[pos].clear(); return false; }
	}
	cns[pos-N]=randint(0,K);
	return true;
}

bool change_e(){
	V<bool>dp(N+M); {
		StronglyConnectedComponents scc(g);
		V<bool>ep(N+M);
		ep[scc[bns]]=true;
		rep(i,N+M)if(ep[i]){
			int oi=scc.belong(i)[0];
			each(e,g[oi])ep[scc[e]]=true;
		}
		rep(i,N+M)dp[i]=ep[scc[i]];
	}

	int pos=-1;
	int b=-1;
	rep(i,N,N+M)if(dp[i] && !g[i].empty()){
		rep(j,2){
			if(inLR(0,g[i][j],N)){
				pos=i; b=j; break;
			}
		}
		if(pos>=0)break;
	}
	rep(3){
		int npos=randint(N,N+M);
		if(!dp[npos])continue;
		if(g[npos].empty())continue;
		rep(j,2){
			if(inLR(0,g[npos][j],N)){
				pos=npos; b=j; break;
			}
		}
	}

	int TIMELIMIT=0.03*CLOCKS_PER_SEC;
	int ti=clock();
	while(clock()-ti<TIMELIMIT){
		int to=randint(N,N+M);
		if(pos==to || g[pos][0]==to || g[pos][1]==to)continue;
		if(dp[to])continue;
		bool fn=true;
		rep(i,N+M){
			each(e,g[i])if(!inter_check(i,e,pos,to)){ fn=false; break; }
			if(!fn)break;
		}
		if(fn){
			int pto=g[pos][b];
			g[pos][b]=to;
			if(StronglyConnectedComponents(g).dag.size()<N+M)g[pos][b]=pto;
			else return true;
		}
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

	ans.resize(N); rep(i,N)ans[i]=i;
	bns=s_idxs[0]+N;
	g.resize(N+M);
	cns.resize(M,-1);
	cns[bns-N]=randint(0,K);
	g[bns].eb(d_idxs[0]);
	g[bns].eb(d_idxs[1]);

	{ // add 分別機
		int TIMELIMIT=0.50*CLOCKS_PER_SEC;
		int cnt=M-1;
		while(clock()-ti<TIMELIMIT){
			int pos=randint(N,N+M);
			if(g[pos].empty())if(add_e(pos))if(--cnt==0)break;
		}
	}

	{ // 「分別機to処理機」を「分別機to分別機」に変える
		int TIMELIMIT=1.00*CLOCKS_PER_SEC;
		score=cal_score();
		int cnt=0;
		while(clock()-ti<TIMELIMIT){
			if(change_e())++cnt;
		}
		out(cnt);
	}

	ans_adj();
	{ // どの分別機を使うか調整
		int TIMELIMIT=1.70*CLOCKS_PER_SEC;
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
		out(cnt);
	}

	out(ans);
	out(bns);
	rep(i,N,N+M){
		if(cns[i-N]<0)out(-1);
		else out(cns[i-N],g[i]);
	}
}
