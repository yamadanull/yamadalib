#include "../../template/template.hpp"
using namespace yamada;

// mod M 内でプラマイ2以内しか動けない中で、各値が一回ずつ現れる 0~to 間のパスを作成
// sig==1: 最後が正
// sig==0: 最後が負
vl cal_path(ll to,ll M,bool sig){
	assert(inLR<ll>(1,to,M));
	if(!sig){
		auto ans=cal_path(M-to,M,1);
		each(a,ans)a=-a;
		return ans;
	}
	vl ans;
	if(to==M-1)ans.resize(M-1,1);
	else if(to%2){
		rep(i,0,to+1,2)ans.eb(2);
		rep(i,to+1,M-2)ans.eb(1);
		rep(i,-1,to,2)ans.eb(2);
	}
	else{
		rep(i,0,to-2,2)ans.eb(2);
		ans.eb(-1);
		rep(i,-1,to-3,2)ans.eb(-2);
		rep(i,to+1,M-1)ans.eb(-1);
		ans.eb(-2); ans.eb(1);
	}
	assert(ans.size()==M-1);
	return ans;
}

vvl cal(ll N,vl D){
	each(d,D)assert(d<=N/3);
	ll M=D.size();
	if(D.size()==1){
		assert(D[0]==1);
		vv(ll,ans,N,N);
		ans[0].clear();
		rep(i,1,N){
			rep(j,N)ans[i][j]=j;
			swap(ans[i][N-1],ans[i][i]);
		}
		return ans;
	}

	array<vvl,2> bns;
	ll G=0;
	ll H=D.back();
	{
		auto E=D;
		E.pop_back();
		each(e,E)G=gcd(e,G);
		assert(gcd(G,H)==1);
		each(e,E)e/=G;

		rep(i,2)bns[i]=cal(N/G+i,E);
	}
	assert(G<H);

	auto remfix_max=[&](ll rem)->ll{ // mod G
		rem=Modulo(rem,G);
		ll ans=N/G*G+rem;
		while(ans>=N)ans-=G;
		return ans;
	};
	auto remfix_min=[&](ll rem)->ll{return Modulo(rem,G); };
	auto get_bnsG=[&](ll from,ll to)->vl{
		assert(from!=to);
		assert((from-to)%G==0);

		auto B=bns[from%G<N%G][abs(from-to)/G];
		if(from==remfix_min(from%G)){
			each(b,B)b=b*G+from;
		}
		else{
			assert(from==remfix_max(from));
			each(b,B)b=from-b*G;
		}
		return B;
	};

	vvl ans(N);
	vl inv(G); rep(i,G)inv[Modulo(H*i,G)]=i;
	rep(TO,1,N)if(TO%G){
		// addH が正なら、その後最上位に行く
		// addH が負なら、その後最下位に行く
		auto addH=cal_path(inv[TO%G],G,!(TO==remfix_max(TO)));
		auto& A=ans[TO];
		rep(bi,G){
			ll st=(bi==0? 0: A.back()+addH[bi-1]*H);
			ll go=-1;
			if(bi<G-1){
				ll nst=-1;
				if(addH[bi]>0)nst=remfix_max(st+addH[bi]*H);
				else nst=remfix_min(st+addH[bi]*H);
				go=nst-addH[bi]*H;
			}
			else go=TO;
			each(a,get_bnsG(st,go))A.eb(a);
		}
		out("A:",A);
		cout.flush();
	}
	rep(TO,G,N,G){
		auto Lans=bns[0<N%G][TO/G]; each(a,Lans)a*=G;
		ll n=Lans.size();
		assert(n>0);

		ll Rst=remfix_max(H*2);
		out("Lans:",Lans);
		out("Rst:",Rst);
		cout.flush();
		ll m=-1;
		rep(i,n-1)if((Lans[i]-Rst)%H==0)m=i+1;
		assert(m>=0);

		ll Rgo=Lans[m]-H; if(Rgo<0)Rgo+=H*2;
		auto Rans=ans[Lans[m]];
		assert(!Rans.empty());
		auto& A=ans[TO];
		rep(i,m)A.eb(Lans[i]);
		rep(i,n,N)A.eb(Rans[i]);
		rep(i,m,n)A.eb(Lans[i]);
		/* out("A:",A); */
	}
	return ans;
}

void tc()
{
	inl(N,M);
	vl D(M); in(D); sort(all(D));
	each(d,D)if(d==1)die(mkiota(N));
	ll g=0;
	each(d,D)g=gcd(d,g);
	if(g>=2)die(-1);
	auto ans=cal(N,D);
	out(ans[1]);
}
void yamada::solve() { inl(T); while(T--)tc(); }
