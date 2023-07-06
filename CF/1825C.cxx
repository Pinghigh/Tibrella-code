#ifdef __GCC__
#pragma GCC optimize("O3", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("avx2", "sse4a", "bmi1", "bmi2", "lzcnt", "popcnt", "fma")
#endif

#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>

using std::cin;
using std::cout;
using std::sort;

const char endl = '\n';

int t;
int n, m;
int tmp;
std::vector<int> ren;
std::bitset<1e5+1> st;
int toRight, toLeft, mxlef, mxrig;
int ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ren.reserve(1e5+5);

    cin >> t;
    while (t--) {
        st.reset();
        ren.resize(0);
        toLeft = toRight = ans = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> tmp;
            switch (tmp) {
                case (-1): ++toLeft; break;
                case (-2): ++toRight; break;
                default: ren.emplace_back(tmp);
            }
        }
        sort(ren.begin(), ren.end());
        if (toLeft > toRight) {
            ++ans;
            mxlef = mxrig = ren.back();
            for (auto rit = ren.rbegin() + 1; rit != ren.rend(); ++rit) {
                while (*rit < mxlef && toLeft && mxlef) {
                    mxlef--;
                    toLeft--;
                    ++ans;
                }
                mxlef = *rit;
                ++ans;
            }
            while (mxrig <= m && toRight) {
                --toRight;
                ++mxrig;
                ++ans;
            }
        } else {
            ++ans;
            mxlef = mxrig = ren.front();
            for (auto it = ren.begin() + 1; it != ren.end(); ++it) {
                while (*it < mxlef && toRight && mxrig <= m) {
                    mxrig++;
                    toRight--;
                    ++ans;
                }
                mxrig = *it;
                ++ans;
            }
            while (mxlef && toLeft) {
                --toLeft;
                --mxlef;
                ++ans;
            }
        }
        cout << ans << endl;
    }

    return 0;
}