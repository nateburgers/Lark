// lrkp_union.cpp
#include <lrkp_union.h>

#include <vector>

int main()
{
    using namespace LarkCompiler::lrkp;
    using namespace std;

    Union<int, char> foo(3);
    const int bar = foo.as<int>();
    int baz = foo.as<int>();
    foo.destroy<int>();

    Union<int, vector<int>> qux(2);
    qux.destroy<vector<int>>();

    return 0;
}
