#include "../../template/template.hpp"
#include "../../math/affine-transformation.hpp"
#include "../../modint/montgomery-modint.hpp"
#include "../../lct/link-cut-tree.hpp"
using namespace yamada;

using mint = LazyMontgomeryModInt<998244353>;
using Aff=Affine<mint>;
using T=pair<Aff,Aff>;
T F(T X,T Y){ return{X.fi*Y.fi,Y.se*X.se}; }
T TS(T X){ return{X.se,X.fi}; }

using LCT=LinkCutTree<T,F,TS>;

void yamada::solve()
{
	IN(N,Q);
	while(Q--){
		auto OP=CHR();
		if(OP=='L'){
		}
		else if(OP=='C'){
		}
		else if(OP=='U'){
		}
		else{
		}
	}
}
