#include "../../template/template.hpp"
#include "../../enumerate/sequences.hpp"
using namespace yamada;

string msktoS(ll msk,ll N){
	string ans;
	rep(i,N)ans+=(msk>>i&1? '#':'.');
	return ans;
}

const int M=16;
bool naive(ll A,ll B,ll C){
	bool ans=0;
	rep(msk,1<<M)if(lsb(msk+1)==A)rep(nsk,1<<M)if(lsb(nsk+1)==B){
		ll ksk=0;
		rep(i,M)if(msk>>i&1)rep(j,M)if(nsk>>j&1){
			ksk|=1LL<<(i^j);
		}
		if(lsb(ksk+1)==C){
			ans=1;
			err(A,B,C);
			err(msktoS(msk,M));
			err(msktoS(nsk,M));
			err(msktoS(ksk,M));
			return 1;
		}
	}
	return ans;
}
bool cal(ll A,ll B,ll C){
	return 0;
}

void exper(){
	rep(a,1,M)rep(b,a,M){
		vl Cs;
		rep(c,b,M){
			/* if(msb(b)<msb(c)){ */
			/* 	/1* if(!naive(a,b,c))err(a,b,c); *1/ */
			/* 	continue; */
			/* } */
			auto ans=naive(a,b,c);
			if(!ans)Cs.eb(c);
		}
		err(a,b,Cs);
	}
}

void yamada::solve()
{
	/* exper(); */
	out(naive(1,5,6));
	/* inl(a,b,c); */
	/* naive(a,b,c); */
	/* err(ans,bns); */
}
