#include "../../template/template.hpp"
#include "../../modint/arbitrary-modint.hpp"

using mint=ArbitraryModInt;
using vm=vector<mint>; // 1
using vvm=vector<vm>; // 2
using vvvm=vector<vvm>; // 3
using vvvvm=vector<vvvm>; // 4
using vvvvvm=vector<vvvvm>; // 5
using vvvvvvm=vector<vvvvvm>; // 6
using vvvvvvvm=vector<vvvvvvm>; // 7
void yamada::solve()
{
	inl(N,X,Y,K,M);
	mint::set_mod(M);
	vvvvvvvm dp(1,vvvvvvm(1,vvvvvm(1,vvvvm(1,vvvm(1,vvm(1,vm(K+1)))))));
	dp[0][0][0][0][0][0][0]=1;
	rep(i,N){
		vvvvvvvm ep(i+2,vvvvvvm(i+2,vvvvvm(i+2,vvvvm(i+2,vvvm(i+2,vvm(i+2,vm(K+1)))))));
		rep(i0,i+1)rep(i1,i+1)rep(j0,i+1)rep(j1,i+1)rep(k0,i+1)rep(k1,i+1)rep(c,K+1)if(dp[i0][i1][j0][j1][k0][k1][c]!=0){
			ll i2=i-i0-i1;
			ll j2=i-j0-j1;
			ll k2=i-k0-k1;
			{ // 012
				ll I0=i0+1;
				ll I1=i1;
				ll J0=j0;
				ll J1=j0+1;
				ll K0=k0;
				ll K1=k1;
				ll C=c;
				C+=i1+i2;
				C+=j2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
			{ // 021
				ll I0=i0+1;
				ll I1=i1;
				ll J0=j0;
				ll J1=j0;
				ll K0=k0;
				ll K1=k1+1;
				ll C=c;
				C+=i1+i2;
				C+=k2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
			{ // 102
				ll I0=i0;
				ll I1=i1+1;
				ll J0=j0+1;
				ll J1=j0;
				ll K0=k0;
				ll K1=k1;
				ll C=c;
				C+=i2;
				C+=j1+j2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
			{ // 120
				ll I0=i0;
				ll I1=i1+1;
				ll J0=j0;
				ll J1=j0;
				ll K0=k0+1;
				ll K1=k1;
				ll C=c;
				C+=i2;
				C+=k1+k2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
			{ // 201
				ll I0=i0;
				ll I1=i1;
				ll J0=j0+1;
				ll J1=j0;
				ll K0=k0;
				ll K1=k1+1;
				ll C=c;
				C+=j1+j2;
				C+=k2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
			{ // 210
				ll I0=i0;
				ll I1=i1;
				ll J0=j0;
				ll J1=j0+1;
				ll K0=k0+1;
				ll K1=k1;
				ll C=c;
				C+=j2;
				C+=k1+k2;
				if(C<=K)ep[I0][I1][J0][J1][K0][K1][C]+=dp[i0][i1][j0][j1][k0][k1][c];
			}
		}
		dp.swap(ep);
	}

	mint ans=0;
	rep(j0,N+1)rep(j1,N+1)rep(k0,N+1)rep(k1,N+1)ans+=dp[X][Y][j0][j1][k0][k1][K];
	out(ans);
}
