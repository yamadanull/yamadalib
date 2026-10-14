#include "../../template/template.hpp"
#include "../../math/rational.hpp"
#include "../../misc/sequences.hpp"

void yamada::solve()
{
	inl(N);
	ll M=20;
	auto A=LengthFixedSequences(N,false,1,M);
	each(a,A){
		Rational sum=0;
		each(e,a){
			sum+=Rational(1,e*e);
		}
		if(sum==1)die(a);
	}
}
