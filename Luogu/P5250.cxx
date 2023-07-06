#include <algorithm>
#include <iostream>
#include <set>

using std::cin;
using std::cout;

using i32 = int;

std::set<i32> s;
i32 n, op, x;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> op >> x;
        if (--op) {
            if (s.empty())
                cout << "Empty\n";
            else {
                auto it = s.lower_bound(x);
                auto itp = it;
                --itp;
                if (it != s.begin() &&(it == s.end() || *it - x >= x - *itp))
                    cout << *(--it) << '\n';
                else
                    cout << *it << '\n';
                s.erase(it);
            }
        } else {
            if (s.find(x) != s.end())
                cout << "Already Exist\n";
            else
                s.emplace(x);
        }
    }

    return 0;
}