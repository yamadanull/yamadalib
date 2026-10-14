#include "../../template/template.hpp"
#include "../../graph/graph-template.hpp"

void yamada::solve()
{
	auto check=[](UnweightedGraph &g,V<bool> &fn,vl &A)->bool{
		ll N=g.size();
		vvl Bs;
		{
			vl C;
			rep(i,N)if(!fn[i])C.eb(A[i]);
			sort(all(C));
			do{
				vl B(N);
				ll cnt=0;
				rep(i,N){
					if(fn[i])B[i]=A[i];
					else B[i]=C[cnt++];
				}
				Bs.eb(B);
			}while(nxp(C));
		}

		ll cnt=0;
		each(B,Bs){
			bool ok=true;
			rep(u,N)each(v,g[u])if(B[u]>=B[v]){ ok=false; break; }
			if(ok){
				if(++cnt>=2)return false;
			}
		}

		assert(cnt==1);
		/* if(cnt==0)out(fn); */
		return cnt;
	};

	inl(N,M);
	auto g=graph(N,M,true);
	vl A(N); in(A); each(a,A)--a;

	ll ans=infLL;
	rep(S,1<<N){
		V<bool> fn(N);
		rep(i,N)if(S>>i&1)fn[i]=true;
		if(check(g,fn,A))amin(ans,popcnt(S));
		out(S); cout.flush();
	}

	out(ans); cout.flush();
	rep(S,1<<N)if(popcnt(S)==ans){
		V<bool> fn(N);
		rep(i,N)if(S>>i&1)fn[i]=true;
		if(check(g,fn,A))out(fn);
	}
}
