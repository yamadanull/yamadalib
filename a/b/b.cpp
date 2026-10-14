#include "../../template/multitest-template.hpp"
#include "../../segment-tree/segment-tree.hpp"
#include "../../monoid/generate-monoid.hpp"
using namespace yamada;

const int M=16;
const int K=6;
using T=array<array<ll,M>,M>;
T ti(){
	T ans;
	each(a,ans|views::join)a=-infLL;
	return ans;
}
T F(T X,T Y){
	if(X==ti())return Y;
	if(Y==ti())return X;
	T ans=ti();
	rep(i,M)rep(j,M)if(x[i][j]>=0)rep(I,M)rep(J,M)if(y[I][J]>=0){
		rep(k,K){
			ll bns=x[i][j]+y[I][J];
			bns-=(j%3==0);
			bns-=(I%3==0);
			ll j2=j^(k*3);
			ll I2=I^(k*3);
			bns+=(j2%3==0);
			bns+=(I2%3==0);
			amax(ans[i][J],bns);
		}
	}
	return ans;
}
T genT(ll A,ll B){
	T ans=ti();
	rep(k,K){
		ll a=A^(k*3);
		ll b=B^(k*3);
		ans[a][b]=0;
		ans[a][b]+=(a%3==0);
		ans[a][b]+=(b%3==0);
	}
	return ans;
}
using Mono=MyMonoid<T,F,ti>;

void yamada::solve()
{
	inl(N,Q);
	vl A(N); in(A);
	vc<T> init(N);
	SegmentTree<Mono> seg(init);
}
