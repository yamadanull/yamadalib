#include "../../template/template.hpp"
#include "../../shortest-path/bfs.hpp"
#include "../../data-structure/union-find.hpp"
#include "../../misc/chmin-top2.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	inl(H,W,K);
	auto idx=[&](ll i,ll j)->ll{return i*W+j;};
	vs S(H); in(S);
	vl di{-1,0,1,0};
	vl dj{0,-1,0,1};
	UnweightedGraph g(H*W);
	UnionFind uf(H*W);
	rep(i,H)rep(j,W)if(S[i][j]!='#'){
		rep(x,4){
			ll I=i+di[x];
			ll J=j+dj[x];
			if(!inLR(0LL,I,H))continue;
			if(!inLR(0LL,J,W))continue;
			if(S[I][J]=='#')continue;
			if(S[i][j]=='B' && S[I][J]=='B')continue;
			g[idx(i,j)].eb(idx(I,J));
			if(S[i][j]=='W' && S[I][J]=='W')uf.unite(idx(i,j),idx(I,J));
		}
	}

	if(K%2==0){
		rep(i,H)rep(j,W)if(S[i][j]=='B'){
			rep(x,4){
				ll I=i+di[x];
				ll J=j+dj[x];
				if(!inLR(0LL,I,H))continue;
				if(!inLR(0LL,J,W))continue;
				if(S[I][J]=='W'){
					if(K==2)die("Yes");
					if(uf.size(idx(I,J))>=2)die("Yes");
				}
			}
		}
		die("No");
	}

	V<int> st0,st1;
	rep(i,H)rep(j,W)if(S[i][j]=='B'){
		if((i+j)%2)st1.eb(idx(i,j));
		else st0.eb(idx(i,j));
	}

	auto dp0=bfs(g,st0);
	auto dp1=bfs(g,st1);
	rep(i,H)rep(j,W)if(S[i][j]=='B'){
		ll d=((i+j)%2? dp0[idx(i,j)]:dp1[idx(i,j)]);
		if(0<=d && d<=K)die("Yes");
	}
	die("No");
}
