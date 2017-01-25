#include "lrkt_union.h"

struct Point {
    int d_x;
    int d_y;

    Point(int x, int y)
    : d_x(x)
    , d_y(y)
    {
    }
};

void foo()
{
    using namespace LarkCompiler;
    lrkt::Union<int, Point> bar(3);
    bar.as<char>() = 'a';
    bar.replace<int, Point>(2, 3);
}
