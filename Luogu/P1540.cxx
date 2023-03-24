#include <bitset>
#include <iostream>
#include <queue>

using namespace std;

#define N 1145

bitset< N > dict;
queue< int > mem;
int m, n;
int word;
int cnt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n;

    for (int i = 0; i < n; i++) {
        cin >> word;
        if (dict[word]) {
            continue;
        } else {
            cnt++;
            mem.push(word);
            dict[word] = 1;
        }
        if (mem.size() > m) {
            dict[mem.front()] = 0;
            mem.pop();
        }
    }

    cout << cnt;

    return 0;
}
