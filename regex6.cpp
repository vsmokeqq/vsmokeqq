#include <regex>
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;

int main() {
    string data;
    cin >> data;

    regex reg("ab{2,4}a");
    auto pos = data.cbegin();
    auto end = data.cend();
    smatch m;
    for (; regex_search(pos, end, m, reg); pos = m.suffix().first) {
        cout << "match:  " << m.str() << endl;
    }
}