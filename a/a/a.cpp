#include "../../template/template.hpp"
 
void yamada::solve()
{
	IN(S=STR);
	S[0]^=32;
	out(string("Of")+S);
}
