#include "template.hpp"
// テスト用

void yamada::solve()
{
	/* vector<int> A = {3,1,4,1,5}; */
	/* auto B=MAP(a,A){return a*a+1;}; */
	/* EACH(b,B){ */
	/* 	yamada::out(b,b,b); */
	/* 	yamada::out=b; */
	/* }; */
	vector<tuple<int, int>> A{{1,2},{3,4}};
	/* err(A); */

	// タプルをそのまま渡す
	auto B = A | Map << [](auto t) {
		return get<0>(t) + get<1>(t);
	}|ranges::to<vector>();

	// タプルを展開する
	auto C = A | Map << [](int x, int y) {
		return x + y;
	}|ranges::to<vector>();

	auto D=C|Map<<[&](int x)->int{
		return x*x+1;
	}|ranges::to<vector>();

	err(C);
	err(D);
	YesNo(A|All<<[](int x,int y)->bool{return (x+y)%2==1;});
}
