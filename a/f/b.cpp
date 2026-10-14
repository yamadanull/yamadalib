#include "../../template/multitest-template.hpp"
#include "../../hashmap/hashmap.hpp"

const int LG=60;
void yamada::solve()
{
	auto get_nxt=[&](ll i,ll j)->vp{
		vp ans;
		ans.eb(i+1,j/2);
		if(j>0)ans.eb(i,j-1);
		ans.eb(i,j+1);
		if(i>0){
			ans.eb(i-1,j*2);
			ans.eb(i-1,j*2+1);
		}
		return ans;
	};

	inl(sj,si,tj,ti);
	if(si<LG)rep(si)sj/=2;
	else sj=0;
	if(ti<LG)rep(ti)tj/=2;
	else tj=0;
	/* out("si,sj,ti,sj:",si,sj,ti,tj); */

	queue<pl> q;
	HashMap<pl,ll> dist;
	dist[mkp(si,sj)]=0;
	q.emplace(si,sj);

	while(1){
		auto[i,j]=q.front(); q.pop();
		ll d=dist[mkp(i,j)];
		/* fout(i,j,":",d); */
		if(i==ti && j==tj)die(d);

		each2(I,J,get_nxt(i,j)){
			if(!dist.count(mkp(I,J))){
				dist[mkp(I,J)]=d+1;
				q.emplace(I,J);
			}
		}
	}
}
