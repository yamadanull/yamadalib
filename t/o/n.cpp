#include "../../template/template.hpp"

void yamada::solve()
{
	inl(N,M);
	vl P(1<<N); in(P); each(p,P)--p;
	vl W(M),L(M); in2(W,L); each(w,W)--w; each(l,L)--l;

	ll ans=0;
	rep(S,1LL<<(1<<N)){
		V<bool>bit(1<<N);
		rep(i,1<<N)if(S>>i&1)bit[i]=true;

		vv(ll,fn,1<<N,1<<N,-1);
		vl Q=P;
		rep(i,N){
			vl R;
			rep(j,0,Q.size(),2){
				if(bit[Q[j]]==bit[Q[j+1]]){
					if(Q[j]<Q[j+1]){
						R.eb(Q[j]);
						fn[Q[j]][Q[j+1]]=1;
						fn[Q[j+1]][Q[j]]=0;
					}
					else{
						R.eb(Q[j+1]);
						fn[Q[j]][Q[j+1]]=0;
						fn[Q[j+1]][Q[j]]=1;
					}
				}
				else{
					if(Q[j]>Q[j+1]){
						R.eb(Q[j]);
						fn[Q[j]][Q[j+1]]=1;
						fn[Q[j+1]][Q[j]]=0;
					}
					else{
						R.eb(Q[j+1]);
						fn[Q[j]][Q[j+1]]=0;
						fn[Q[j+1]][Q[j]]=1;
					}
				}
			}
			Q=R;
		}

		bool bns=true;
		rep(i,M)if(fn[W[i]][L[i]]!=1)bns=false;
		if(bns)++ans;
	}
	out(ans);
}
