#include "../../template/template.hpp"
using namespace yamada;

const array<ll,7> NPFI={1,2,3,4,5,6,7};
const array<ll,7> NPSE={-1,0,-1,-1,-1,1,1};

// [count(Aのあまり)、(Bのあまり)、(素のC)、(素のD)、...]
map<array<ll,8>,bool> memo;
bool naive(array<ll,8> &A){
	if(memo.count(A))return memo[A];
	auto flip=[&](auto& a){
		swap(a[0],a[1]);
		swap(a[2],a[3]);
		swap(a[5],a[6]);
	};
	each(n,p,zip(NPFI,NPSE))if(A[n]){
		auto B=A;
		--B[n];
		if(p>=0)++B[p];
		flip(B);
		if(!naive(B))return memo[A]=1;
	}
	return memo[A]=0;
}
ll F(array<ll,8> A){
	auto[a,b,c,d,e,f,g,h]=A;
	ll ans=(b-a)*4+(d-c);
	if((f-g)%2==0){
		ll bns=(f-g);
		ans-=bns;
	}
	else{
		ll bns=f-g-2;
		ans-=bns;
	}

	/* for(auto i:{e,h})ans+=i%2; */
	return ans;
}
bool cal(array<ll,8> A){
	return F(A)>0;
}

void exper(){
	inl(M);
	vv(ll,dp,M,M);
	rep(a,M)rep(b,M)rep(c,M)rep(d,M)rep(e,M)rep(f,M)rep(g,M)rep(h,M){
		array<ll,8> A={a*2,b*2,c,d,e,f,g,h};
		auto ans=naive(A);
		auto B=A;
		B[0]/=2,B[1]/=2;
		auto bns=F(B);
		if(ans!=(bns>0)){
			if(bns>0){
				err(e,h,ans,-bns);
				assert(dp[e][h]<=0);
				amin(dp[e][h],-bns);
			}
			else{
				err(e,h,ans,-bns+1);
				assert(dp[e][h]>=0);
				amax(dp[e][h],-bns+1);
			}
		}
	}
	rep(i,M)err(i,dp[i]);
}

void yamada::solve()
{
	exper();
	/* inl(a,b,c,d,e,f,g,h); */
	/* array<ll,8> A={a*2,b*2,c,d,e,f,g,h}; */
	/* fout(naive(A)?"Alice":"Bob"); */
}
