#include "../../template/template.hpp"

void yamada::solve()
{
	const ll log=60;
	const ll M=26;
	auto tc=[&](){
		char c; in(c); c-='a';
		inl(E);
		if(E==0){
			if(c==0)out("a");
			else out("aa");
			return;
		}

		vl ans{infLL};
		rep(t,log){
			// t回現れる
			if(E%(1LL<<t))break;
			// c以外の部分の長さ
			ll e=E/(1LL<<t);
			if(e>=M)continue;

			vl bns;
			rep(i,e){
				if(i<c)bns.eb(i);
				else bns.eb(i+1);
			}
			rep(t)bns.eb(c);
			sort(all(bns));
			amin(ans,bns);
		}

		if(ans[0]==infLL)out(-1);
		else{
			string S;
			each(a,ans)S+='a'+a;
			out(S);
		}
	};

	inl(T);
	while(T--)tc();
}
