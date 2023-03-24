#include <iostream>
// #include <queue>

using namespace std;

#define N 10000100
#define min(a, b) (tree[a] < tree[b] ? (a) : (b))

int tree[N], tsize;
int n;

void qswap(int& a, int& b) {
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
    //     cout << "[swap] " << tmp << ' ' << a << endl;
}

void ins(int a) {
    tree[++tsize] = a;
    int now, nex;
    now = tsize;
    while (now > 1) {
        nex = now >> 1;
        if (tree[now] >= tree[nex]) {
            break;
        }
        qswap(tree[now], tree[nex]);
        now = nex;
    }
    //     cout << "[insert] " << a << " size: " << tsize << " pos: " << now << endl;
}

void del() {
    //    cout << "[delete] " << tree[1] << endl;
    tree[1] = tree[tsize--];

    int now, nex;
    now = 1;
    while ((now << 1) <= (tsize)) {
        nex = now << 1;
        nex = (nex >= tsize) ? nex : min(nex, nex + 1);  // 此处 min 输入返回的都是下标
        if (tree[now] <= tree[nex]) break;
        qswap(tree[now], tree[nex]);
        now = nex;
        //        cout << "now_____" << now << endl;
    }
    //    tsize --;
}

int main() {
    // freopen("P3378_4.in","r",stdin); freopen("out.txt","w",stdout);
    tree[0] = 0x3f3f3f3f;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int beh, dat;
    cin >> n;
    while (n--) {
        //         cout << "---" << n << endl;
        cin >> beh;
        switch (beh) {
        case (1):
            cin >> dat;
            ins(dat);
            break;
        case (2): cout << tree[1] << endl; break;
        case (3): del(); break;
        }
        //        cout << "data ";
        //        for (int i = 1; i <= tsize; i ++) cout << tree[i] << ' ';
        //        cout << endl;
    }

    return 0;
}