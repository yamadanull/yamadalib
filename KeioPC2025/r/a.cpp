#include "../../template/template.hpp"
#include "../../string/rolling-hash.hpp"

void yamada::solve()
{
	using H=roriha::Hash;
	const ll M=2e5;
	inl(N,Q);
	ins(S);

	roriha rh(S);
	VV<H> hs(M); each(h,hs)h.eb(H::set(0));
	vvp lr(M);
	vvl sz(M); each(s,sz)s.eb(0);
	auto get_H=[&](ll I,ll R)->H{
		ll hi=ub(sz[I],R)-1;
		auto ans=hs[I][hi];
		if(hi==lr[I].size())return ans;

		ll rem=R-sz[I][hi];
		auto[l,r]=lr[I][hi];
		amin(r,l+rem);
		return pfma(ans,rh.pw[rem],rh.get(l,r));
	};
	auto get_C=[&](ll I,ll R)->char{
		ll hi=ub(sz[I],R)-1;
		if(hi==lr[I].size())return 0;
		ll rem=R-sz[I][hi];
		auto[l,r]=lr[I][hi];
		return S[l+rem];
	};
	while(Q--){
		inl(op);
		if(op==1){
			inl(k,l,r); --k; --l;
			lr[k].eb(l,r);
			hs[k].eb(pfma(hs[k].back(),rh.pw[r-l],rh.get(l,r)));
			sz[k].eb(sz[k].back()+r-l);
		}
		else{
			inl(I,J); --I; --J;
			auto check=[&](ll R)->bool{
				return get_H(I,R)==get_H(J,R);
			};

			ll R=bisect(0LL,infLL,check)-1;
			/* out(R); */
			auto c0=get_C(I,R);
			auto c1=get_C(J,R);
			if(c0<c1)out("<");
			else if(c0==c1)out("=");
			else out(">");
		}
	}
}
