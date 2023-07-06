#include <iostream>

using namespace std;

#define N 1010

int data[N][N];
int n, a, b, num;
struct Node {
    int l, r;
    int nums;
    bool operator<(Node example) { if (example.l) }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    while (n--) {
        cin >> a >> b >> num;
        data[a][b] = num;
    }

    return 0;
}
