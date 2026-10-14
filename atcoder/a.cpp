
#include "modint.hpp"

#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<long long> VL;
typedef vector<VL> VVL;
typedef long long LL;
#define all(a) (a).begin(), (a).end()
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define ALL(a)  (a).begin(),(a).end()
#define pb push_back

#include <atcoder/modint>
using mint = atcoder::modint998244353;

int p2[11];

int n,m,k;

void sol(){
  int A[m],B[m];
  rep(i,m){cin>>A[i]>>B[i]; A[i]--;B[i]--;}
  mint ans=1;
  mint ppp=1/mint(m);
  for(int iii=1;iii<n;iii++){
    mint dp[p2[n]][k+1]={};
    dp[p2[iii]][0]=1;
    rep(j,k){
      rep(i,p2[n])rep(kai,m){
        int ido=i;
        if(i&p2[A[kai]]){ido|=p2[B[kai]];}
        if(i&p2[B[kai]]){ido|=p2[A[kai]];}
        dp[ido][j+1]+=dp[i][j]*ppp;
      }
    }
    rep(i,p2[n-1]){
      ans+=dp[i*2+1][k];
    }
  }
  cout<<ans.val()<<endl;
}

int main() {
  p2[0]=1;
  rep(i,10){p2[i+1]=p2[i]*2;}
  while(1){
    cin>>n>>m>>k;
    if(n==0){return 0;}
    sol();
  }
}
