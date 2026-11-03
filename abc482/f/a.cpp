#include "../../template/template.hpp"
#include "../../prime/fast-factorize.hpp"

void yamada::solve()
{
	IN(N,M);
	vp PC;
	vl dp(M,infLL);
	vl q; // 距離がdである頂点
	each(p,c,factor_count(N)){
		PC.eb(p,c);
	}
	each(d,divisors(N)){
		if(amin(dp[d%M],1)){
			q.eb(d%M);
		}
	}
	rep(d,2,infLL){
		if(q.empty())break;
		auto nq=q;
		each(p,c,PC){
			auto seeing=nq;
			rep(c){
				vl nseeing;
				each(u,seeing){
					ll v=i128(u)*p%M;
					if(amin(dp[v],d)){
						nseeing.eb(v);
						nq.eb(v);
					}
				}
				seeing.swap(nseeing);
			}
		}
		Sort(q);
		vl nq2;
		each(u,nq)if(!BinarySearch(q,u))nq2.eb(u);
		q.swap(nq2);
	}

	each(d,dp){
		out(d==infLL?-1:d);
	}
}
