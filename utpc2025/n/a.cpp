#include "../../template/template.hpp"
#include "../../math/rational.hpp"
#include "../../math/bigint-all.hpp"
#include "../../modulo/binomial.hpp"
#include "../../modint/montgomery-modint.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
using F = RationalBase<bigint,bigint>;
Binomial<mint> binom;
constexpr ll E=1e5;

void cal(ll N,vl A){
	rep(pc,1,N){
		V<P<F,ll>> sum_msk;
		rep(msk,1<<N)if(popcnt(msk)==pc){
			F sum(0);
			rep(i,N)if(msk>>i&1){
				sum+=F(1,A[i]);
			}
			sum_msk.eb(sum,msk);
		}
		sort(all(sum_msk));
		rep(i,sum_msk.size()-1){
			auto[sum,msk]=sum_msk[i];
			auto[tum,nsk]=sum_msk[i+1];
			if(tum-sum<=F(1,E)){
				out("Yes");
				out(pc);
				vvl ans(2);
				vl p{msk,nsk};
				rep(b,2)rep(i,N)if(p[b]>>i&1)ans[b].eb(i+1);
				each(a,ans)out(a);
				return;
			}
		}
	}
	out("No");
}
void dal(ll N,vl A){
	const ll K=logl(N)+1;
	ll M=-1;
	rep(i,1,N){
		if(binom(N,i).get()>E*K){
			M=i;
			break;
		}
	}

	assert(M>=1);
	vl cnt(E*K);
	ll ans=-1;
	auto dfs=[&](auto&& self,vl cur)->void{
		if(cur.size()==M){
			lld sum=0;
			each(c,cur)sum+=(lld)1/A[c];
			if(cnt[sum*E]++>=1)ans=sum*E;
			return;
		}
		ll lim=(cur.empty()? 0:cur.back()+1);
		rep(i,lim,N){
			cur.eb(i);
			self(self,cur);
			if(ans>=0)return;
			cur.pop_back();
		}
	}; dfs(dfs,vl());

	out("Yes");
	out(M);
	vvl bns;
	auto efs=[&](auto&& self,vl cur)->void{
		if(cur.size()==M){
			lld sum=0;
			each(c,cur)sum+=(lld)1/A[c];
			ll cns=sum*E;
			if(cns==ans)bns.eb(cur);
			return;
		}
		ll lim=(cur.empty()? 0:cur.back()+1);
		rep(i,lim,N){
			cur.eb(i);
			self(self,cur);
			if(bns.size()>=2)return;
			cur.pop_back();
		}
	}; efs(efs,vl());
	each(b,bns){
		each(e,b)++e;
		out(b);
	}
}

void yamada::solve()
{
	constexpr ll DIV=21;
	inl(N);
	amin(N,DIV);
	vl A(N); in(A);
	{
		vvl pos(E);
		rep(i,N)pos[A[i]-1].eb(i);
		each(p,pos)if(p.size()>=2){
			out("Yes");
			out(1);
			rep(2)out(p[0]+1);
			return;
		}
	}
	if(N<DIV)cal(N,A);
	else dal(N,A);
}
