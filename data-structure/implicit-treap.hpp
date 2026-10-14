#pragma once

template<class S> struct treapnode{
	void *lch_ = nullptr,*rch_ = nullptr; //子node
	int pri_=0; //優先度
	int cnt_=1; //部分木サイズ
	S data_=S();
	treapnode(){}
	treapnode(int priority,const S &data): pri_(priority),data_(data){}
	void init(int priority,const S &data){ pri_=priority,data_=data; }
	treapnode *lch()const{ return static_cast<treapnode*>(lch_); }
	treapnode *rch()const{ return static_cast<treapnode*>(rch_); }
	S &data(){ return data_; }
	int cnt()const{ return cnt_; }
	int pri()const{ return pri_; }
	int cntL()const{ return lch() ? lch()->cnt() : 0; }
	int cntR()const{ return rch() ? rch()->cnt() : 0; }
	void update_cnt(){ cnt_=cntL()+cntR()+1; }
	void pushup(){ update_cnt(); }
	void pushdown(){}
	constexpr static bool needup(){ return false; } //cnt更新以外にpushup()が必要か
	using data_type = S;
};

template<class Node> struct treap{
	using ll = long long;
	using S = typename Node::data_type;
	Node *root = nullptr;

	static inline vector<Node> nodePool; //nodeの実体プール 一度確保したら再確保しないよう注意
	static inline int nodePoolUsed=0; //nodeの実体使用数
	static inline const S dmy=S();

	treap(Node *tree): root(tree){}
	treap() = default;
	treap(const vector<S> &ini){ init(ini); }

	static void init(
			int mxNd=0, //!<[in] ノードをmxNd個事前確保(0なら何もしない)
			int seed=-1 //!<[in] 乱数シードをseedで初期化(-1なら時刻使用)
			){
		if (mxNd>0){
			if (nodePool.empty()) nodePool.resize(mxNd); //ノード事前確保(未確保時のみ)
		}
		newPri((int)seed); //乱数シード設定
	}

	void init(const vector<S> &ini){ //O(N)で新規構築
		int n=(int)ini.size();
		if (n==0){
			root=nullptr;
			return;
		}
		vector<Node*> v;  v.reserve(n);
		int step=0x7fffffff/(n+1);
		for (int i=1; i<=n; ++i) v.push_back(newNode(S(),0x7fffffff-i*step));

		vector<pair<int,int>> lr;  lr.reserve(n);
		lr.emplace_back(0,n-1);
		for (int i=0; i<n; ++i){
			auto [l,r]=lr[i];
			int m=(l+r)>>1;
			v[i]->data()=ini[m];
			if (l<m){
				lr.emplace_back(l,m-1);
				v[i]->lch_=v[lr.size()-1];
			}
			if (m<r){
				lr.emplace_back(m+1,r);
				v[i]->rch_=v[lr.size()-1];
			}
		}
		root=v[0];
		pushupAll(root);
	}
	void assign(const vector<S> &v){ init(v); }

	bool empty()const{ return !root; }
	int size()const{ return root ? (int)root->cnt() : 0; }

	S operator[](int i)const{
		assert(0<=i && i<size());
		Node *v=root;
		while (v->pushdown(),v->cntL()!=i){
			if (v->cntL()<i) i-=v->cntL()+1,v=v->rch();
			else v=v->lch();
		}
		return v->data();
	}

	template<class E,class G> void apply(ll i,const E &y,G g){
		assert(0<=i && i<size());
		static vector<Node*> bf;
		//iまで降りる
		Node *v=root;
		while (true){
			v->pushdown();
			if (Node::needup()) bf.push_back(v);
			if (v->cntL()==i) break;
			if (v->cntL()<i) i-=v->cntL()+1,v=v->rch();
			else v=v->lch();
		}
		//適用
		v->data()=g(y,v->data());
		//祖先列を下から順にpushup
		if (Node::needup()) while (!bf.empty()) bf.back()->pushup(),bf.pop_back();
	}
	void set(ll i,const S &data){
		apply(i,data,[](const S &y,const S &x){ (void)x; return y; });
	}

	bool contains(const S &data){
		return Contains(root,data, [&](Node *v,int cntP){ (void)cntP; return data<v->data(); });
	}

	void insert(int idx,const S &data){
		insert(data, [&](Node *v,int cntP){ (void)cntP; return idx<=cntP+v->cntL(); });
	}
	void insert(const S &data){
		insert(data, [&](Node *v,int cntP){ (void)cntP; return data<v->data(); });
	}
	void insertq(const S &data){
		insertq(data, [&](Node *v,int cntP){ (void)cntP; return data<v->data(); });
	}
	void push_back(const S &data){ insert(size(),data); }

	pair<const S&,int> floorandidx(const S &data){
		auto [lv,rv,i]=search( [&](Node *v,int cntP){ (void)cntP; return data<v->data(); });
		if (lv) return {lv->data(),i};
		else   return {dmy,       i};
	}
	const S& floor(const S& data){ return floorandidx(data).first; }
	int   flooridx(const S& data){ return floorandidx(data).second; }

	pair<const S&,int> ceilandidx(const S &data){
		auto [lv,rv,i]=search( [&](Node *v,int cntP){ (void)cntP; return data<=v->data(); });
		if (rv) return {rv->data(),i+1};
		else   return {dmy,       i+1};
	}
	const S& ceil(const S& data){ return ceilandidx(data).first; }
	int   ceilidx(const S& data){ return ceilandidx(data).second; }

	void erasei(int idx){
		assert(0<=idx && idx<size());
		auto [ltree,mtree,rtree]=split3(root,(int)idx,(int)idx+1);
		root=merge(ltree,rtree);
	}

	bool erasex(const S &data){
		bool ret=true;
		auto [ltree,remtree]=split(root,0, [&](Node *v,int cntP){ (void)cntP; return data<=v->data(); });
		auto [mtree,rtree]=split(remtree,1);
		if (!mtree || mtree->data()!=data){
			ret=false;
			root=merge3(ltree,mtree,rtree);
		}
		else root=merge(ltree,rtree);
		return ret;
	}

	void rotate(int l,int r,int m){
		auto [t0,t1,t2,t3]=split4(root,(int)l,(int)m,(int)r+1);
		root=merge4(t0,t2,t1,t3); //root再代入、pri同点で変わる可能性を考慮
	}

	treap splitfront(ll i){
		Node *l;
		tie(l,root)=split(root,(int)i+1);
		return treap(l);
	}
	treap splitback(ll i){
		Node *r;
		tie(root,r)=split(root,(int)i);
		return treap(r);
	}
	template<class Pr> requires is_class_v<Pr> treap splitfront(Pr pr){
		Node *l;
		tie(l,root)=split(root,0,pr);
		return treap(l);
	}
	template<class Pr> requires is_class_v<Pr> treap splitback(Pr pr){
		Node *r;
		tie(root,r)=split(root,0,pr);
		return treap(r);
	}
	treap splitlower(const S &data){
		Node *l;
		tie(l,root)=split(root,0, [&](Node *v,int cntP){ (void)cntP; return data<v->data(); });
		return treap(l);
	}
	treap splitupper(const S &data){
		Node *r;
		tie(root,r)=split(root,0, [&](Node *v,int cntP){ (void)cntP; return data<=v->data(); });
		return treap(r);
	}

	void mergefront(treap &tr){
		root=merge(tr.root,root);
		tr.root=nullptr;
	}
	void mergeback(treap &tr){
		root=merge(root,tr.root);
		tr.root=nullptr;
	}

	void dumptree()const{ dumptree(root,0); }
	void dump(){ treap(*this).dumpcore(); }

	/*---- utility ----*/

	/*! @brief 新規nodeをpoolから生成 なければnew */
	static Node *newNode(const S &data,int pri=-1){
		assert(!nodePool.empty());
		if (pri==-1) pri=newPri();
		if (nodePoolUsed >= (int)nodePool.size()) return new Node(pri,data);
		Node *v = &nodePool[nodePoolUsed++];
		v->init(pri,data);
		return v;
	}

	/*! @brief 線形合同法で0~2^31-1の乱数を発生 */
	static int newPri(
			int s=-1 //!<[in] seedをsに設定(呼び出し初回以外は無視) -1:時刻使用
			){
		static int x = (s!=-1) ? s :
			(int)chrono::system_clock::now().time_since_epoch().count();
		return x=(1103515245*x+12345)&0x7fffffff;
	}

	void pushupAll(Node *tree){ //treeはnullptr不可
		if (tree->lch()) pushupAll(tree->lch());
		if (tree->rch()) pushupAll(tree->rch());
		tree->pushup();
	}

	Node *merge(Node *a,Node *b){ //aの右にbを結合
		if (!a || !b) return a ? a : b;
		Node *ret;
		if (a->pri() > b->pri()) a->pushdown(),a->rch_=merge(a->rch(),b),ret=a;
		else                     b->pushdown(),b->lch_=merge(a,b->lch()),ret=b;
		ret->pushup();
		return ret;
	}
	Node *merge3(Node *l,Node *m,Node *r){ return merge(l,merge(m,r)); }
	Node *merge4(Node *l,Node *m,Node *n,Node *r){ return merge(l,merge3(m,n,r)); }

	//pr(v,cntP)のfalse/trueで分割 左側がfalse
	template<class Pr> requires is_class_v<Pr>
		pair<Node*,Node*> split(Node *nd,int cntP/*サブ木外左側ノード数*/,Pr pr){
			if (!nd) return {nullptr,nullptr};
			nd->pushdown();
			if (!pr(nd,cntP)){ //現nodeを左へ
				auto [ltree,rtree]=split(nd->rch(),cntP+nd->cntL()+1,pr);
				nd->rch_=ltree;
				nd->pushup();
				return {nd,rtree};
			}
			else{ //現nodeを右へ
				auto [ltree,rtree]=split(nd->lch(),cntP,pr);
				nd->lch_=rtree;
				nd->pushup();
				return {ltree,nd};
			}
		}
	pair<Node*,Node*> split(Node *nd,int idx){ //添字idx未満と以上に分割
		return split(nd,0, [&](Node *v,int cntP){ (void)cntP; return idx<=cntP+v->cntL(); });
	}
	tuple<Node*,Node*,Node*> split3(Node *nd,int i,int j){//3分割[0,i),[i,j),[j,)
		auto [lmtree,rtree]=split(nd,j);
		auto [ltree,mtree]=split(lmtree,i);
		return {ltree,mtree,rtree};
	}
	tuple<Node*,Node*,Node*,Node*> split4(Node *nd,int i,int j,int k){//4分割
		auto [tree012,tree3]=split(nd,k);
		auto [tree0,tree1,tree2]=split3(tree012,i,j);
		return {tree0,tree1,tree2,tree3};
	}

	//dataをpr(v,cntP)のfalse/true境界に挿入  uniq=true:重複したら挿入しない
	template<class Pr,bool uniq=false> requires is_class_v<Pr>
		void insert(const S &data,Pr pr){
			static vector<Node*> bf;
			int nPri=newPri();
			//-- 優先度が低くなるまで下る
			//v:pri小のサブ木, pv:vの格納場所(lch等), bf:pri大の祖先列
			Node **pv=&root,*v=root;
			int cntP=0;//サブ木外左側ノード数
			while (v && v->pri()>=nPri){
				v->pushdown();
				if (uniq){//一致するデータなら即終了
					if (v->data()==data){ bf.clear(); return; }
				}
				bf.push_back(v);
				if (!pr(v,cntP)) pv=(Node**)&(v->rch_),cntP+=v->cntL()+1;
				else            pv=(Node**)&(v->lch_);
				v=*pv;
			}
			if (uniq){//同じ値が下にあれば即終了
				if (Contains(v,data,pr)){ bf.clear(); return; }
			}
			//-- 優先度低のサブ木vを分割して左右の子にする
			auto [ltree,rtree]=split(v,cntP,pr);
			*pv=merge3(ltree,newNode(data,nPri),rtree);
			//-- 祖先列を下から順にpushup
			while (!bf.empty()) bf.back()->pushup(),bf.pop_back();
		}

	template<class Pr> void insertq(const S &data,Pr pr){
		insert<Pr,true>(data,pr);
	}

	/*!
	  @brief   pr(v,cntP)のfalse/true境界を得る
	  @return <false側v, true側v, false側vのindex> vがないときはnullptr
	 */
	template<class Pr> requires is_class_v<Pr>
	tuple<Node*,Node*,int> search(Pr pr){
		Node *lv=nullptr,*rv=nullptr,*v=root;
		int cntP=0; //vのサブ木外左側ノード数
		while (v){
			v->pushdown();
			if (pr(v,cntP)) rv=v,moveL(v,cntP);//現在位置 true 左の子へ
			else           lv=v,moveR(v,cntP);//現在位置false 右の子へ
		}
		return {lv,rv,cntP-1};
	}

	template<class Pr> requires is_class_v<Pr>
	bool Contains(Node *tree,const S &data,Pr pr){//true:treeの下に一致する値有
		Node *v=tree;
		while (v){
			v->pushdown();
			if (v->data()==data) return true;
			v = pr(v,0) ? v->lch() : v->rch();
		}
		return false;
	}

	//moveL:左の子へ移動、moveR:右の子へ移動、cntP:vのサブ木外左側ノード数
	static void moveL(Node *&v,int &cntP){ (void)cntP,v=v->lch(); }
	static void moveR(Node *&v,int &cntP){ cntP+=v->cntL()+1,v=v->rch(); }

	void dumptree(Node *v,ll p)const{
		if (!v)return;
		dumptree(v->lch(),-abs(p)-1);
		cout << string(4*abs(p),' ') << ((p<0) ? "/- " : "`- ") << v->data() << '\n';
		dumptree(v->rch(),abs(p)+1);
	}
#if 1
	void dumpcore(){//vectorにして表示
		vector<S> v;
		for (int i=0; i<size(); ++i){
			v.push_back((*this)[i]);
		}
		if (!v.empty()) dumpstring::dumpNd("",v,args().labels({"i"}));
	}
#endif
};
/*
   - ---- 定義
   using tre = treap<treapnode<ll>>;
   tre::init(mxNd); //ノードmxNd個予め確保(概ね初期長+挿入回数)
   tre tr;          //空で初期化
   tre tr(ini);     //vector<T> ini で初期化
   - 複数定義
   vector<tre> trs(N);                //空でN個作られる
   for (auto &&tr: trs) tr.init(ini); //初期構築したい場合

   - ---- 各種操作
   bool b=tr.empty();
   ll N=tr.size();
   tr.assign(v);     //vector<T> vで上書き
   ll x=tr[i];
   tr.set(i,x);                                //tr[i]←x
   tr.apply(i,x,[](ll y,ll z){ return y+z; }); //tr[i]←tr[i]+x
   tr.push_back(x);   //末尾にx挿入
   tr.insert(i,x);    //位置iにxを挿入
   tr.insert(x,pred); //pred(v,cntP)のfalse/true境界に挿入
   tr.erasei(i);      //位置iを削除
   tr.rotate(l,r,m);  //[l,r]をmがlになるようrotate
   auto trL=tr.splitfront(i);    //[0,i]を切り出し
   auto trR=tr.splitback(i);     //[i,N-1]を切り出し
   auto trL=tr.splitfront(pred); //pred(v,cntP)のfalse側を切り出し
   auto trR=tr.splitback(pred);  //pred(v,cntP)の true側を切り出し
   tr.mergefront(trL); //先頭に結合
   tr.mergeback (trR); //末尾に結合

   - ---- ソート済配列(昇順)として使うとき
   tr.contains(x);      //true:xを含む
   tr.insert(x);        //昇順位置にxを挿入
   tr.insertq(x);       //昇順位置にxを挿入、重複削除
   bool b=tr.erasex(x); //xを1つ削除 true:x有,削除 false:x無
   ll i=tr.flooridx(x); //x以下最大の位置 ないとき-1
   ll i=tr. ceilidx(x); //x以上最小の位置 ないときtr.size()
   ll x=tr.floor(x);    //x以下最大の値 ないとき不定、番兵等で防ぐ
   ll x=tr.ceil (x);    //x以上最小の値 ないとき不定、番兵等で防ぐ
   auto[va,j]=tr.floorandidx(x); //x以下最大の値vaと位置j ないときj=-1
   auto[va,j]=tr. ceilandidx(x); //x以上最小の値vaと位置j ないときj=tr.size()
   auto trL=tr.splitlower(x);   //x以下を切り出し
   auto trR=tr.splitupper(x);   //x以上を切り出し
 */


template<class S,auto op,auto e,class F,auto mapping,auto composition,auto id>
struct lazytreapnode: public treapnode<S>{
	static_assert(is_convertible_v<decltype(op),function<S(S,S)>>,"op must work as S(S,S)");
	static_assert(is_convertible_v<decltype(e),function<S()>>,"e must work as S()");
	static_assert(is_convertible_v<decltype(mapping),function<S(F,S)>>,"mapping must work as F(F,S)");
	static_assert(is_convertible_v<decltype(composition),function<F(F,F)>>,"compostiion must work as F(F,F)");
	static_assert(is_convertible_v<decltype(id),function<F()>>,"id must work as F()");
	using P = treapnode<S>;
	S acc_=e(); //サブ木内総積
	F lazy=id(); //子以下(自分の値含む)に遅延して施す写像 自分のaccは適用済
	bool rev=false; //true:サブ木内反転順
	lazytreapnode(){}
	lazytreapnode(int priority,const S &data)
		: treapnode<S>(priority,data),acc_(data){}
	void init(int priority,const S &data){
		treapnode<S>::init(priority,data);
		acc_=data;
	}
	static S E(){ return e(); }
	static S Op(const S &a,const S &b){ return op(a,b); }
	static S Op3(const S &a,const S &b,const S &c){ return op(op(a,b),c); }
	static S Mapping(const F &f,const S &x){ return mapping(f,x); }
	lazytreapnode *lch()const{ return static_cast<lazytreapnode*>(P::lch_); }
	lazytreapnode *rch()const{ return static_cast<lazytreapnode*>(P::rch_); }
	S acc()const{ return acc_; }
	S accL()const{ return lch() ? lch()->acc() : e(); }
	S accR()const{ return rch() ? rch()->acc() : e(); }
	void fliprev(){ rev = !rev; }
	bool isLazyId(){ return lazy==id(); } //Fに依存した高速な判定に変える選択肢有
	void applyParentLazy(F parentLazy){
		acc_= mapping(parentLazy,acc_);
		lazy=composition(parentLazy,lazy);
	}
	void update_acc(){ acc_=Op3(accL(),P::data(),accR()); }
	void pushup(){ P::update_cnt(),update_acc(); }
	void pushdown(){ //子(左,自分の値,右)に、遅延で適用するもの(rev,lazy)を適用
		if (rev){//反転の伝搬
			rev=false;
			swap(P::lch_,P::rch_);
			if (lch()) lch()->fliprev();
			if (rch()) rch()->fliprev();
		}
		if (!isLazyId()){//lazyの伝搬
						 //自分の値にlazy適用
			P::data_=mapping(lazy,P::data_);
			//左右の子のaccとlazyに自分のlazyを適用
			if (lch()) lch()->applyParentLazy(lazy);
			if (rch()) rch()->applyParentLazy(lazy);
			lazy=id();
		}
	}
	constexpr static bool needup(){ return true; } //cnt更新以外にpushup()が必要か
	using mapping_type = F;
};

template<class Node> struct lazytreap: public treap<Node>{
	using int = long long;
	using P = treap<Node>;
	using S = typename Node::data_type;
	using F = typename Node::mapping_type;
	/*---- I/F ----*/
	lazytreap() = default;
	lazytreap(const vector<S> &ini):P(ini){}

	void apply(int l,int r,const F &f){
		auto [ltree,mtree,rtree]=P::split3(P::root,(int)l,(int)r+1);
		if (mtree) mtree->applyParentLazy(f);
		P::root=P::merge3(ltree,mtree,rtree); //root再代入、pri同点で変わる可能性を考慮
	}
	void apply(ll i,const F &f){
		assert(0<=i && i<P::size());
		auto mapping=[](const F &y,const S &x){ return Node::Mapping(y,x); };
		P::apply(i,f,mapping);
	}

	S get(int l,int r){
		//[l,r]をpredL,predRで指定 cntPはvのサブ木外左側ノード数
		auto predL=[&](Node *v,int cntP){ int i=cntP+v->cntL(); return l<=i; };
		auto predR=[&](Node *v,int cntP){ int i=cntP+v->cntL(); return i<=r; };

		//-- フェーズ1:vが範囲に入る(predL,predR=true)まで下る
		Node *v=P::root;
		int cntP=0;//vサブ木外左側node数
		while (v){//下るループ
			v->pushdown();
			if (!predL(v,cntP)) P::moveR(v,cntP);//現在nodeが左外のとき 右子へ
			else if (!predR(v,cntP)) P::moveL(v,cntP);//現在nodeが右外のとき 左子へ
			else break; //範囲内のとき break
		}
		if (!v) return Node::E();//範囲内のnodeが無いとき
		S prod=v->data();

		{//-- フェーズ2a：左の子の[l,*]を積算
			Node *u=v; int cntPu=cntP;
			P::moveL(u,cntPu);//左子へ移動
			while (u){
				u->pushdown();
				if (predL(u,cntPu)){//範囲内のとき 左子へ移動
					prod=Node::Op3(u->data(),u->accR(),prod);//累積←現nodeの値＊右子の値＊現累積
					P::moveL(u,cntPu);
				}
				else P::moveR(u,cntPu);//左外のとき 右子へ移動
			}
		}
		{//-- フェーズ2b：右の子の[*,r]を積算
			Node *u=v; int cntPu=cntP;
			P::moveR(u,cntPu);//右子へ移動
			while (u){
				u->pushdown();
				if (predR(u,cntPu)){//範囲内のとき 右子へ移動
					prod=Node::Op3(prod,u->accL(),u->data());//累積←現累積＊左子の値＊現nodeの値
					P::moveR(u,cntPu);
				}
				else P::moveL(u,cntPu);//右外のとき 左子へ移動
			}
		}
		return prod;
	}

	void reverse(int l,int r){
		auto [ltree,mtree,rtree]=P::split3(P::root,(int)l,(int)r+1);
		if (mtree) mtree->fliprev();
		P::root=P::merge3(ltree,mtree,rtree); //root再代入、pri同点で変わる可能性を考慮
	}

	//-------- 区間max/min専用I/F --------
	int findNextGE(int i,S x){
		static const bool isMax = S(2) < Node::Op(S(1),S(3));
		auto ret = searchLAcc((int)i,[&](Node *v,int cntP,S accP){
				S curAcc=Node::Op3(accP,v->accL(),v->data());
				return isMax ? curAcc>=x : curAcc<=x;
				});
		return std::get<2>(ret)+1;
	}

	int findPrevGE(int i,S x){
		static const bool isMax = S(2) < Node::Op(S(1),S(3));
		auto ret = searchRAcc((int)i,[&](Node *v,int cntP,S accP){
				S curAcc=Node::Op3(v->data(),v->accR(),accP);
				return isMax ? curAcc>=x : curAcc<=x;
				});
		return std::get<2>(ret)-1;
	}

	pair<int,S> findPeakL(int l,int r){
		S x=get(l,r);
		return {findNextGE(l,x),x};
	}

	pair<int,S> findPeakR(int l,int r){
		S x=get(l,r);
		return {findPrevGE(r,x),x};
	}

	/*---- utility ----*/

	/*!
	  @brief   pr(v,cntP,accP)のfalse/true境界を得る
cntP:vのサブ木外左側ノード数、accP:vのサブ木外左側かつl以降の総積
pr(単位元)=trueも可
@return <false側v, true側v, false側vのindex, [l,false側v]総積>
vがないときはnullptr
	 */
	template<class Pr> requires is_class_v<Pr>
	tuple<Node*,Node*,int,S> searchLAcc(int l,Pr pr){
		auto [lTree,tree]=P::split(P::root,l); //位置l以降を分離

		Node *lv=nullptr,*rv=nullptr,*v=tree;
		int cntP=l; //vのサブ木外左側ノード数
		S accP=Node::E(); //vのサブ木外左側の総積
		while (v){
			v->pushdown();
			if (pr(v,cntP,accP)){//現在位置 true 左の子へ
				rv=v;
				v=v->lch();
			}
			else{//現在位置false 右の子へ
				lv=v;
				cntP+=v->cntL()+1;
				accP=Node::Op3(accP,v->accL(),v->data());//左累積←現累積＊左子の値＊現nodeの値
				v=v->rch();
			}
		}

		P::root=P::merge(lTree,tree); //分離を戻す root再代入、pri同点で変わる可能性を考慮
		return {lv,rv,cntP-1,accP};
	}
	/*!
	  @brief   pr(v,cntP,accP)のtrue/false境界を得る
cntP:vのサブ木外左側ノード数、accP:vのサブ木外右側かつr以前の総積
pr(単位元)=trueも可
@return <true側v, false側v, false側vのindex, [false側v,r]総積>
vがないときはnullptr
	 */
	template<class Pr> requires is_class_v<Pr>
	tuple<Node*,Node*,int,S> searchRAcc(int r,Pr pr){
		auto [tree,rTree]=P::split(P::root,r+1); //位置r以前を分離

		Node *lv=nullptr,*rv=nullptr,*v=tree;
		int cntP=0; //vのサブ木外左側ノード数
		S accP=Node::E(); //vのサブ木外右側かつr以前の総積
		while (v){
			v->pushdown();
			if (pr(v,cntP,accP)){//現在位置 true 右の子へ
				lv=v;
				cntP+=v->cntL()+1;
				v=v->rch();
			}
			else{//現在位置false 左の子へ
				rv=v;
				accP=Node::Op3(v->data(),v->accR(),accP);//右累積←現nodeの値＊右子の値＊現累積
				v=v->lch();
			}
		}
		P::root=P::merge(tree,rTree); //分離を戻す root再代入、pri同点で変わる可能性を考慮
		return {lv,rv,cntP,accP};
	}
};
/*
   - ---- 定義
   using tre = lazytreap<lazytreapnode<SS,op,e,FF,mapping,composition,id>>;
   tre::init(mxNd); //ノードmxNd個予め確保(概ね初期長+挿入回数)
   tre tr;          //空で初期化
   tre tr(ini);     //vector<T> ini で初期化
   - 複数定義
   vector<tre> trs(N);                //空でN個作られる
   for (auto &&tr: trs) tr.init(ini); //初期構築したい場合

   - ---- 各種操作
   bool b=tr.empty();
   ll N=tr.size();
   tr.assign(v);     //vector<T> vで上書き
   ll x=tr[i];
   tr.set(i,x);      //tr[i]←x            位置iにx代入
   tr.apply(i,y);    //tr[i]←f(y,tr[i])   位置iに適用関数使用
   tr.apply(l,r,y);  //tr[i]←f(y,tr[l~r]) [l,r]に適用関数使用
   tr.push_back(x);  //末尾にx挿入
   tr.insert(i,x);   //位置iにx挿入
   tr.insert(x);     //昇順位置xに挿入
   tr.insert(x,pred);//pred(v,cntP)のfalse/true境界に挿入
   tr.erasei(i);     //位置iを削除
   bool b=tr.erasex(x); //xを1つ削除(昇順格納時のみ) true:x有,削除 false:x無
   ll x=tr.get(l,r); //[l,r]の総積取得
   tr.reverse(l,r);  //[l,r]を反転
   tr.rotate(l,r,m); //[l,r]をmがlになるようrotate
   auto trL=tr.splitfront(i);   //[0,i]を切り出し
   auto trR=tr.splitback(i);    //[i,N-1]を切り出し
   auto trL=tr.splitfront(pred);//pred(v,cntP)のfalse側を切り出し
   auto trR=tr.splitback(pred); //pred(v,cntP)の true側を切り出し
   tr.mergefront(trL); //先頭に結合
   tr.mergeback (trR); //末尾に結合

   - ---- ソート済配列(昇順)として使うとき
   tr.contains(x);      //true:xを含む
   tr.insert(x);        //昇順位置にxを挿入
   tr.insertq(x);       //昇順位置にxを挿入、重複削除
   bool b=tr.erasex(x); //xを1つ削除 true:x有,削除 false:x無
   ll i=tr.flooridx(x); //x以下最大の位置 ないとき-1
   ll i=tr. ceilidx(x); //x以上最小の位置 ないときtr.size()
   ll x=tr.floor(x);    //x以下最大の値 ないとき不定、番兵等で防ぐ
   ll x=tr.ceil (x);    //x以上最小の値 ないとき不定、番兵等で防ぐ
   auto[va,j]=tr.floorandidx(x); //x以下最大の値vaと位置j ないときj=-1
   auto[va,j]=tr. ceilandidx(x); //x以上最小の値vaと位置j ないときj=tr.size()
   auto trL=tr.splitlower(x);   //x以下を切り出し
   auto trR=tr.splitupper(x);   //x以上を切り出し

   - ---- 区間max(min)のみの操作 ----
   ll j=tr.findNextGE(i,x);      //i以降で初めてx以上(以下)になる位置
   ll j=tr.findPrevGE(i,x);      //i以前で初めてx以上(以下)になる位置
   auto[i,va]=tr.findPeakL(l,r); //[l,r]内max(min)になる最左位置iと値va
   auto[i,va]=tr.findPeakR(l,r); //[l,r]内max(min)になる最右位置iと値va

   - ---- 各種モノイド・写像
   - 区間加算max取得
   using TT = ll;
   using FF = ll;
   TT op(TT x,TT y) { return max(x,y); }
   TT e() { return -INF; }
   TT mapping(FF f, TT x) { return f+x; }
   FF composition(FF g,FF f) { return g+f; }
   FF id() { return 0; }
 */
