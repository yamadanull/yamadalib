#include "../../template/template.hpp"
using namespace yamada;

void tc()
{
	inl(N,M);
	vv(ll,A,N,N,-1);
	// 0: non-neg
	// 1: neg
	rep(M){
		inl(op,i,j); op--; --i; --j;
		A[i][j]=A[j][i]=op;
	}
	rep(i,N)rep(j,i+1,N)if(A[i][i]==A[j][j]){
		if(A[i][j]!=A[i][i])die("NO");
	}

	ll Pcnt=0;
	rep(i,N)if(!A[i][i])Pcnt++;
	ll Ncnt=N-Pcnt;

	// 正オンリー
	vl L(N,0);
	vl R(N,Pcnt);
	vl ans(N);
	rep(ni,N)if(A[ni][ni]){
		ll sml=0,big=0;
		rep(pi,N)if(!A[pi][pi]){
			if(A[ni][pi])++sml;
			else ++big;
		}

		ans[ni]=-sml-1;
		rep(pi,N)if(!A[pi][pi]){
			if(A[ni][pi])amin(R[pi],sml);
			else amax(L[pi],sml);
		}
	}
	/* out("Pcnt:",Pcnt); */
	/* out("L:",L); */
	/* out("R:",R); */

	vvl Linv(Pcnt);
	rep(i,N)if(!A[i][i])Linv[L[i]].eb(i);

	minpq<pl> q;
	rep(a,Pcnt){
		each(i,Linv[a])q.emplace(R[i],i);
		if(q.empty())die("NO");
		/* out("B"); */
		auto[r,i]=q.top(); q.pop();
		/* out("r,a:",r,a); */
		if(r<=a)die("NO");
		/* out("C"); */
		ans[i]=a+1;
	}

	fout("YES");
	fout(ans);

	rep(i,N)rep(j,N){
		if(A[i][j])assert(ans[i]+ans[j]<0);
		else assert(ans[i]+ans[j]>=0);
	}
}
void yamada::solve() { ini(T); while(T--)tc(); }
