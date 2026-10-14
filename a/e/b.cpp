#include <iostream>
#include <format>
#include <vector>

int main()
{
  // vector<bool>は1要素あたり1bitのみ領域を使用するよう特殊化されている。
  // しかし、出力としては通常のbool配列と同様になるようformatterが特殊化されている
  std::vector<bool> v = {true, false, true};

  std::cout << std::format("{}", v) << std::endl;
}

