#include <iostream>
#include <set>
#include <string>

using i32 = int;

int main() {
    std::multiset<std::string> s;
    i32 a, b, c;
    std::cin >> a >> b >> c;
    while (a--)
        s.emplace("a");
    while (b--)
        s.emplace("b");
    while (c--)
        s.emplace("c");
    while (s.size() > 1) {
        auto h = s.begin(), t = --s.end();
        s.emplace(*h + *t), s.erase(h), s.erase(t);
    }
    std::cout << *s.begin();
}