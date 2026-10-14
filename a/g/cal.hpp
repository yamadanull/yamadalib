using namespace yamada;

vp cal(ll H,ll W,ll R,ll C){
	if(H%2==1 && W%2==0){
		auto ans=cal(W,H,C,R);
		each2(r,c,ans)swap(r,c);
		return ans;
	}

	vp A;
	if(H%2==0){
		rep(i,H)A.eb(i,0);
		repr(i,H){
			if((H-1-i)%2==0)rep(j,1,W)A.eb(i,j);
			if((H-1-i)%2==1)repr(j,1,W)A.eb(i,j);
		}
		assert(A.size()==H*W);

		ll RC_id=-1;
		rep(i,H*W)if(A[i]==mkp(R,C))RC_id=i;

		vp ans(H*W);
		rep(i,H*W)ans[i]=A[(i+RC_id)%(H*W)];
		return ans;
	}

	// 以下、odd x odd
	if((R+C)%2)return vp();

	if(R==H-1){
		auto ans=cal(H,W,H-R-1,C);
		each2(r,c,ans)r=H-r-1;
		return ans;
	}
	if(C==0){
		auto ans=cal(H,W,R,W-C-1);
		each2(r,c,ans)c=W-c-1;
		return ans;
	}

	if(R%2==1){
		repr(j,C+1){
			if(j%2==0)rep(i,R+1)A.eb(i,j);
			if(j%2==1)repr(i,R+1)A.eb(i,j);
		}
		rep(i,R+1,H){
			if(i%2==0)rep(j,W-1)A.eb(i,j);
			if(i%2==1)repr(j,W-1)A.eb(i,j);
		}
		repr(i,H)A.eb(i,W-1);
		repr(j,C+1,W-1){
			if(j%2==1)rep(i,R+1)A.eb(i,j);
			if(j%2==0)repr(i,R+1)A.eb(i,j);
		}
		return A;
	}

	repr(i,R+1)A.eb(i,C);
	rep(i,R+1){
		if(i%2==1)rep(j,C)A.eb(i,j);
		if(i%2==0)repr(j,C)A.eb(i,j);
	}

	rep(j,C+1)A.eb(R+1,j);
	rep(j,C+1,W){
		if(j%2==0)rep(i,R+2)A.eb(i,j);
		if(j%2==1)repr(i,R+2)A.eb(i,j);
	}
	rep(i,R+2,H){
		if(i%2==1)rep(j,W)A.eb(i,j);
		if(i%2==0)repr(j,W)A.eb(i,j);
	}
	assert(A.size()==H*W);
	return A;
}

vvl cal(vl A,vl B){
	ll D=A.size();
	ll N=1;
	each(a,A)N*=a;

	if(D==2){
		auto bns=cal(A[0],A[1],B[0],B[1]); if(bns.empty())return vvl();
		assert(bns.size()==N);
		vv(ll,ans,N,2);
		rep(i,N){
			auto[r,c]=bns[i];
			ans[i][0]=r,ans[i][1]=c;
		}

		rep(i,ans.size()-1){
			ll d=0;
			auto a=ans[i];
			auto b=ans[i+1];
			rep(i,D)d+=abs(a[i]-b[i]);
			assert(d==1);
		}
		return ans;
	}

	auto X=A,Y=B; X.pop_back(),Y.pop_back();

	auto bns=cal(X,Y);
	auto cns=cal(N/A[D-1],A[D-1],0,B[D-1]);
	if(bns.empty() || cns.empty())return vvl();

	vv(ll,ans,N,D);
	rep(ai,cns.size()){
		auto[I,J]=cns[ai];
		rep(di,D-1)ans[ai][di]=bns[I][di];
		ans[ai][D-1]=J;
	}
	return ans;
}
