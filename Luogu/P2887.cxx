#include <algorithm>
#include <iostream>

using namespace std;

#define N 2505

struct c {
    int mn, mx;
} cow[N];

struct s {
    int sun, cnt;
} scr[N];

int cc, l;
int ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> cc >> l;
    for (int i = 1; i <= cc; ++i)
        cin >> cow[i].mn >> cow[i].mx;
    for (int i = 1; i <= l; ++i)
        cin >> scr[i].sun >> scr[i].cnt;

    sort(cow + 1, cow + cc + 1, [](c& a, c& b) {
        if (a.mn == b.mn) return a.mx < b.mx;
        return a.mn > b.mn;
    });
    sort(scr + 1, scr + l + 1, [](s& a, s& b) { return a.sun > b.sun; });

    int pos = 1;
    for (int i = 1; i <= cc; ++i) {
        // while (pos <= l && (!scr[pos].cnt || scr[pos].sun > cow[i].mx))
        //     ++pos;
        // if (pos > l) break;
        // if (scr[pos].sun >= cow[i].mn) ++ans, --scr[pos].cnt;

        for (int j = 1; j <= l; ++j) {
            if (scr[j].cnt && (scr[j].sun <= cow[i].mx && scr[j].sun >= cow[i].mn)) {
                ++ans;
                --scr[j].cnt;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}