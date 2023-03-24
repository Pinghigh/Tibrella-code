#include <iostream>
#include <string>

using namespace std;

#define SI short int
#define N 114514

struct man {
    string name;
    SI l, r;
} men[N];

int n, m;
bool dire;
int s;
int idx;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> dire >> men[i].name;
        if (dire) {
            men[i].l = 1, men[i].r = -1;
        } else {
            men[i].l = -1;
            men[i].r = 1;
        }
    }

    idx = 1;
    while (m--) {
        cin >> dire >> s;
        idx += (dire ? men[idx].r : men[idx].l) * s;
        while (idx > n)
            idx -= n;
        while (idx < 1)
            idx += n;
    }

    cout << men[idx].name;

    return 0;
}
