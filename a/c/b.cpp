#include "../../template/multitest-template.hpp"

void yamada::solve()
{
	// return dist(u,v) >= d
	auto query=[](ll u,ll v,ll d)->bool{
		fout("?",u+1,v+1,d);
		inl(b);
		return b;
	};
	auto answer=[](array<ll,3> uvd){
		auto[u,v,d]=uvd;
		fout("!",u+1,v+1,d);
	};

	inl(N);
	array<ll,3> uvd={0,0,0};

	/* rep(n,1,N){ */
	/* 	auto[u,v,d]=uvd; */
	/* 	if(query(u,n,d+1)){ */
	/* 		d++; */
	/* 		rep(nd,d+1,N){ */
	/* 			if(!query(u,n,nd)){ */
	/* 				d=nd-1; */
	/* 				break; */
	/* 			} */
	/* 		} */

	/* 		if(u!=v && query(v,n,d+1)){ */
	/* 			d++; */
	/* 			rep(nd,d+1,N){ */
	/* 				if(!query(u,n,nd)){ */
	/* 					d=nd-1; */
	/* 					break; */
	/* 				} */
	/* 			} */
	/* 			uvd={v,n,d}; */
	/* 		} */
	/* 		else uvd={u,n,d}; */
	/* 	} */
	/* 	else{ */
	/* 		if(query(v,n,d+1)){ */
	/* 			d++; */
	/* 			rep(nd,d+1,N){ */
	/* 				if(!query(u,n,nd)){ */
	/* 					d=nd-1; */
	/* 					break; */
	/* 				} */
	/* 			} */
	/* 			uvd={v,n,d}; */
	/* 		} */
	/* 		else uvd={u,n,d}; */
	/* 	} */
	/* } */
	answer(uvd);
}
