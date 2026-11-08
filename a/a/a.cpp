#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	IN(N,A=LL*N);
	out(bisearch<ll>(1<<20,-1,[&](ll K)->bool{
		auto B=A;
		vl pos;
		rep(i,N-1)if(abs(B[i+1]-B[i])>K)pos.eb(i+1);
		if(pos.empty())return 1;
		if(len(pos)>=3)return 0;
		if(len(pos)==2){
			ll L=pos[0],R=pos[1];
			Reverse(B|Take(R)|Drop(L));
			rep(i,L,R)B[i]*=2;
			rep(i,N-1)if(abs(B[i+1]-B[i])>K)return 0;
			return 1;
		}

		ll R=pos[0];
		rep(2){
			Reverse(B);
			R=N-R;
			if(N==5&&K==8){
				err(pos);
			}

			repr(L,R){
				auto getb=[&](ll i)->ll{
					if(inLR(L,i,R))return B[R-(i-L)-1]*2;
					return B[i];
				};
				// 真ん中のチェック
				if(L!=R-1){
					ll n0=getb(R-2);
					ll n1=getb(R-1);
					if(abs(n1-n0)>K)break;
				}
				// 両端のチェック
				if(abs(getb(R)-getb(R-1))>K)continue;
				if(L>0 && abs(getb(L)-getb(L-1))>K)continue;
				return 1;
			}
		}
		return 0;
	}));
}
