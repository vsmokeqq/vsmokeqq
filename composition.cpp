#include <iostream>
#include <functional>
#include <cmath>

template <typename _F, typename _G, typename _G1, typename _G11>
class AppFtoG
{
public:
    AppFtoG(_F _f, _G1 _g1, _G _g, _G11 _g11) : f(_f), g1(_g1), g(_g), g11(_g11) { }

    template <typename T>
    T operator () (T x, T y) {
        return f(g1(x), g(g11(x), y));
    }

private:
    _F f;
    _G g;
    _G1 g1;
    _G11 g11;
};

class CompHelp {
public:
    template <typename _F, typename _G, typename _G1, typename _G11>
    auto operator () (_F _f, _G1 _g1, _G _g, _G11 _g11) { return AppFtoG<_F, _G, _G1, _G11>(_f, _g1, _g, _g11); }
};

template<typename F, typename G1, typename G, typename ... G1n>
auto comp(F func, G1 g1, G g, G1n ... g1n) {
    return [=](auto x, auto y) {
        return func(g1(x), g(g1n(x), y)...);
        };
}

int main() {
    auto  f1 = [](int x, int y) { return x + y; };
    auto   f = [](int a, int b, int c, int d) { return a + b + c + d; };
    auto  g1 = [](int x) { return 2 * x * x; };
    auto   g = [](int x, int y) { return x - y + x * y; };
    auto g11 = [](int x) { return x - 3; };
    auto g12 = [](int x) { return x + 5; };
    auto g13 = [](int x) { return x * x; };

    auto h = comp(f, g1, g, g11, g12, g13);
    int x = 1;

    CompHelp Help;
    auto h1 = Help(f1, g1, g, g11);

    std::cout << h1(1, 2);

}