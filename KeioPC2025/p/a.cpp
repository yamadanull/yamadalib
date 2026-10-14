#include "../../template/template.hpp"
#include "../../misc/int_div.hpp"
using namespace yamada;

bool is_ari(vl A){
	ll N=A.size();
	ll MD=A[1]-A[0];
	rep(i,N-1)if(A[i+1]-A[i]!=MD)return 0;
	return 1;
}

ll cal_neg(vl A){
	sort(all(A),[](ll a,ll b)->bool{return abs(a)<abs(b);});
	ll N=A.size();

	ll MD=-1,md_pos=-1,md_neg=-1;
	{
		ll a=-abs(A[0]),b=abs(A[1]);
		MD=b-a;
		if(MD==0)return infLL;
		md_pos=modulo(abs(a),MD);
		md_neg=modulo(b,MD);
	}

	if(md_pos==md_neg){
		ll ans=0;
		ll bns=0;
		for(ll l=0,r=0; l<N; l=r){
			while(r<N && abs(A[l])==abs(A[r]))++r;
			if(r-l==1){
				if(modulo(abs(A[l]),MD)==md_pos){
					if(A[l]<0){
						A[l]*=-1;
						++ans;
					}
					else if(A[l]>0) ++bns;
				}
				else return infLL;
			}
			else if(r-l==2){
				ll pcnt=0;
				rep(i,l,r)if(A[i]>0)pcnt++;
				if(pcnt==0 || pcnt==2){
					++ans;
					++bns;
					A[l]*=-1;
				}
			}
			else return infLL;
		}

		sort(all(A));
		if(is_ari(A))return min(ans,bns);
		return infLL;
	}

	ll ans=0;
	for(ll l=0,r=0; l<N; l=r){
		while(r<N && abs(A[l])==abs(A[r]))++r;
		if(r-l==1){
			if(modulo(abs(A[l]),MD)==md_pos){
				if(A[l]<0){
					A[l]*=-1;
					++ans;
				}
			}
			else if(modulo(abs(A[l]),MD)==md_neg){
				if(A[l]>0){
					++ans;
					A[l]*=-1;
				}
			}
			else return infLL;
		}
		else return infLL;
	}

	sort(all(A));
	if(is_ari(A)){
		ll bns=N-ans;
		each(a,A)if(a==0)--bns;
		return min(ans,bns);
	}
	return infLL;
}

ll cal_pos(vl A){
	ll ans=0;
	ll bns=0;
	ll N=A.size();
	each(a,A){
		if(a<0){
			a*=-1;
			++ans;
		}
		else if(a>0){
			++bns;
		}
	}
	sort(all(A));
	if(is_ari(A))return min(ans,bns);
	return infLL;
}

void tc()
{

	inl(N);
	vl A(N); in(A);
	if(N<=2)die(0);

	ll ans=infLL;
	amin(ans,cal_neg(A));
	amin(ans,cal_pos(A));
	if(ans==infLL)out(-1);
	else out(ans);
}
void yamada::solve() { ini(T); while(T--)tc(); }
