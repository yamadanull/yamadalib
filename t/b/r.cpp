#include "../../template/template.hpp"
#include "../../misc/all.hpp"

void yamada::solve()
{
	out(1); cout.flush();

	ll N=randint(2,50);
	vl A{0};
	rep(i,N)rep(2) A.eb(i);
	randshf(A);
	cerr<<A<<endl;
	out(N); cout.flush();

	ll cnt=0;
	while(1){
		/* assert(cnt<=33); */
		char c; in(c);
		if(c=='?'){
			++cnt;
			inl(K);
			vl I(K); in(I); each(i,I)--i;
			vl cnt(N);
			each(i,I)++cnt[A[i]];

			ll dnt=0;
			each(i,I)if(cnt[A[i]]==1)++dnt;
			out(dnt); cout.flush();
		}
		else{
			assert(c=='!');
			vl I(3); in(I); each(i,I)--i;
			assert(I.size()==3);
			each(i,I){
				assert(A[i]==0);
				assert(randint(0,100)>=1);
			}
			return;
		}
	}
}
