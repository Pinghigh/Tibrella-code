#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

constexpr int MAXN = 1e6 + 514;

string ori, res;
int size;
int p[MAXN];
int mr, mid;
int len;
int l[MAXN], r[MAXN];
int ans;

void str_init(string& a, string& b) {
    b += "$#";
    for (auto ch : a) {
        b += ch;
        b += '#';
    }
    b += '^';
}

void manacher() {
    for (int i = 0; i <= res.size(); ++i) {
        p[i] = (mr > i) ? min(mr - i, p[(mid << 1) - i]) : 1;

        while (res[i + p[i]] == res[i - p[i]]) {
            ++p[i];
        }

        l[i - p[i] + 1] = max(l[i - p[i] + 1], p[i] - 1);
        r[i + p[i] - 1] = max(r[i + p[i] - 1], p[i] - 1);

        if (i + p[i] > mr) {
            mr = i + p[i];
            mid = i;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ori.reserve(MAXN);
    res.reserve(MAXN);

    cin >> ori;

    str_init(ori, res);
    manacher();

    for (int i = 2; i <= res.size(); i += 2) {
        l[i] = max(l[i], l[i - 2] - 2);
    }
    for (int i = res.size(); i >= 0; i -= 2) {
        r[i] = max(r[i], r[i + 2] - 2);
    }

    for (int i = 1; i <= res.size()+1; i += 2) {
        if (l[i] > 0 && r[i] > 0) {
            ans = max(ans, (l[i]) + (r[i]));
        }
    }
    cout << ans << endl;

    return 0;
}