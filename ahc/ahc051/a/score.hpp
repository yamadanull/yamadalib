using namespace yamada;

VV<double> dag_dp(){ // ゴミiが処理機jに行く確率
	StronglyConnectedComponents scc(g);
	assert(scc.dag.size()==N+M);
	vv(double,dp,N,N+M,0); // ゴミiがトポロジカル番号jを通る確率
	rep(i,N){
		dp[i][scc[bns]]=1;
		rep(j,N+M)if(dp[i][j]>0){
			int pos=scc.belong(j)[0];
			if(!g[pos].empty()){
				int u=scc[g[pos][0]];
				int v=scc[g[pos][1]];
				int k=cns[pos-N];
				dp[i][u]+=dp[i][j]*Ps[k][i];
				dp[i][v]+=dp[i][j]*(1-Ps[k][i]);
			}
		}
	}
	vv(double,ret,N,N);
	rep(i,N)rep(j,N)ret[i][j]=dp[i][scc[j]];
	return ret;
}

void ans_adj(){
	auto data=dag_dp();
	V<double>dp(1<<N);
	rep(S,(1<<N)-1){
		int j=popcnt(S); // 処理機jに行かせるゴミを決める
		rep(i,N)if(!(S>>i&1)){
			int T=S|(1<<i);
			amax(dp[T],dp[S]+data[i][j]);
		}
	}

	for(int j=N-1,pos=(1<<N)-1; j>=0; j--){
		assert(popcnt(pos)==j+1);
		rep(i,N)if(pos>>i&1){
			int npos=pos^(1<<i);
			if(dp[npos]+data[i][j]==dp[pos]){
				ans[j]=i;
				pos=npos;
				break;
			}
		}
	}
}

double cal_score(){
	auto data=dag_dp();
	double ret=0;
	rep(j,N)ret+=data[ans[j]][j];
	return ret;
}
