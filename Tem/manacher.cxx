#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::string;

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

constexpr int N = 2e7 + 514;

int n;
string a, b;
int p[N];  // p[i] 表示以第 i 个字符为中心的最长回文子串半径
int res;

void init() {
    b += '$';
    b += '#';
    for (int i = 0; i < n; ++i) {
        b += a[i];
        b += '#';
    }
    b += '^';
    n = b.size();
}

void manacher() {
    int mr = 0, mid;
    for (int i = 1; i < n; ++i) {
        if (i < mr) {
            p[i] = min(p[(mid << 1) - i], mr - i);
        } else {
            p[i] = 1;
        }

        while (b[i - p[i]] == b[i + p[i]]) {
            ++p[i];
        }

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

    a.reserve(N);
    b.reserve(N);

    cin >> a;
    n = a.size();

    init();
    manacher();

    for (int i = 0; i < n; ++i) {  // 最后需要枚举一遍来找出最大值
        res = max(res, p[i]);
    }
    cout << res - 1 << endl;

    return 0;
}