#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

const i64 B = 1e7;
const i64 MOD = B * 10;
struct inf_t {
    std::vector<i64> val;
};

std::istream& operator>>(std::istream& in, inf_t& num) {
    std::string str;
    in >> str;
    i64 tmp = 0;
    i64 f = 1;
    i32 bit = 0;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        ++bit;
        tmp = tmp + f * ((*it) ^ 48);
        f *= 10;
        if (bit > 6) {
            num.val.emplace_back(tmp);
            tmp = 0;
            f = 1;
            bit = 0;
        }
    }
    if (tmp) num.val.emplace_back(tmp);
    return in;
}

std::ostream& operator<<(std::ostream& out, inf_t num) {
    if (!num.val.size())
        out << '0';
    else {
        cout << num.val.back();
        cout.fill('0');
        for (auto it = num.val.rbegin() + 1; it != num.val.rend(); ++it)
            cout << std::setw(7) << *it;
    }
    return out;
}

inf_t operator/(inf_t a, i32 b) {
    i64 tmp = 0;
    inf_t res;
    for (auto it = a.val.rbegin(); it != a.val.rend(); ++it) {
        tmp = tmp * B+ *it;
        res.val.emplace_back(tmp / b);
        tmp %= b;
    }
    std::reverse(res.val.begin(), res.val.end());
    // if (tmp) res.val.emplace_back(tmp);
    while (res.val.size() > 1 && !res.val.back())
        res.val.pop_back();
    return res;
}

inf_t a;
i32 b;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> a >> b;
    cout << a / b;

    // cin >> a;
    // cout << a;

    return 0;
}