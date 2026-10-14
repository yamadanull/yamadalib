#include "../../template/template.hpp"

#include "../../prime/fast-factorize.hpp"

#include <ranges>

/* #include <concepts> */

void yamada::solve()
{
	ll N=10;
	auto A=mkiota(N);
	for(auto& v : A|std::ranges::views::filter([](int n){return n%2==0;})){
		cerr<<v<<"\n";
	}
}
