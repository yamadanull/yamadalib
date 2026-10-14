#include "../../template/template.hpp"
#include "../../math/rational.hpp"
using namespace yamada;

void tc()
{
	inl(N);
	if(N==2 || N==3 || N==5)die("No");
	ll add=N-1;

	vl ans;
	vl ans6={2,2,2,3,3,6};
	if(add==5)ans=ans6;
	if(add==7)ans={2,2,2,3,3,9,9,18};
	if(add==10)ans={2,2,2,3,3,9,18,18,18,18,18};
	if(add==13){
		ans=ans6;
		each(a,ans)a*=3;
		rep(8)ans.eb(3);
	}

	if(ans.empty()){
		ll add8=(3-add%3)%3;
		ll add3=(add-add8*8)/3;

		minpq<ll> q;
		q.push(1);
		rep(add3){
			ll a=q.top(); q.pop();
			rep(4)q.push(a*2);
		}
		rep(add8){
			ll a=q.top(); q.pop();
			rep(9)q.push(a*3);
		}
		while(!q.empty()){
			ll a=q.top(); q.pop();
			ans.eb(a);
		}
	}

	out("Yes");
	out(ans);

	/* { */
	/* 	assert(ans.size()==N); */
	/* 	Rational sum=0; */
	/* 	each(a,ans)sum+=Rational(1,a*a); */
	/* 	assert(sum==1); */
	/* } */
}
void yamada::solve() { ini(T); while(T--)tc(); }
