#include <iostream>
#include <concepts>
#include <vector>
#include <set>

class Rational {
public:
  int numerator;
  int denominator;

  Rational(int num, int den) : numerator(num), denominator(den) {}

  operator double() {
    return double(numerator) / double(denominator);
  }
};

template <typename R, typename ... Ts>
auto IsOneInRange(R min, R max, Ts ... ts) {
  return ((min <= ts && ts <= max) || ...);
}

template <typename R, typename ... Ts>
auto IsAllInRange(R min, R max, Ts ... ts) {
  return ((min <= ts && ts <= max) && ...);
}

template <typename T, typename ... Ts>
auto PushInSet(std::set <T>& s, Ts ... ts) {
  return (s.insert(ts).second && ...);
}

template <typename T, typename ... Ts>
void PushInVector(std::vector <T>& v, Ts ... ts) {
  (v.push_back(ts), ...);
  return;
}


int main() {
  std::cout << std::boolalpha;
  std::cout << IsOneInRange(1, 2, 3, 4, 5, 6, 7, 9) << '\n';
  std::cout << IsAllInRange(2, 10, 3, 9, 3, 5, 3, 4, 5) << '\n';

  std::set <int> s;
  std::cout << PushInSet(s, 3, 389, 323, 578345, 3891237) << '\n';
  for (auto i : s) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::vector <Rational> v = {Rational(1, 10)};
  PushInVector(v, Rational(10, 3), Rational(3, 5), Rational(9, 7));



  return 0;
}
