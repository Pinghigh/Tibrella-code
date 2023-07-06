#include <iostream>
#include <map>

using namespace std;

#define N 50010
#define mmin(a, b) ((a) < (b) ? (a) : (b))

int l, n, m;
int dis[N];

struct Node {
    int data;
    int left;
    int right;
    int sum;
    bool operator<(Node example) {
        return left < example.left;
    }
} stones[N];
map<int, Node> list;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> l >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> dis[i];
        stones[i].data = i;
    }
    dis[n] = l;
    stones[0].left = dis[0];
    stones[0].right = dis[1] - dis[0];
    list[0] = stones[0];
    for (int i = 1; i < n; i++) {
        stones[i].left = dis[i] - dis[i - 1];
        stones[i].right = dis[i + 1] - dis[i];
        stones[i].sum = dis[i + 1] - dis[i - 1];
        list[i] = stones[i];
    }

    auto it = list.begin();
    auto sit = list.begin();
    auto eit = list.end();
    eit--;
    sit++;
    int cho = 0;
    while (m--) {
        sit = list.begin();
        eit = list.end();
        eit--;
        sit++;
        cho = (*it).first;
        if ((*it).second.left <= (*eit).second.right) {
            while ((*it).second.left == (*(sit)).second.left) {
                cho = ((*it).second.sum < (*sit).second.sum) ? (*it).first : (*sit).first;
                sit++;
            }
            if ((*it).second.left == (*eit).second.right) {
                cho = it->second.sum < eit->second.sum ? it->first : eit->first;
                sit++;
            }
        }
        list.erase(cho);
    }
    cout << mmin(eit->second.right, list->begin().second.left);

    return 0;
}
