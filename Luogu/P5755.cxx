#include <algorithm>
#include <iostream>
#include <string>


using namespace std;

#define N 320010

bool comp(string a, string b) {
    for (int i = 0, end = a.size() < b.size() ? a.size() : b.size(); i < end; i++) {
        if (a[i] < b[i])
            return 1;
        else if (a[i] > b[i])
            return 0;
    }
    return (a.size() <= b.size() ? 1 : 0);
}

string list[N];
int tail, res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (cin >> list[tail++]);

    sort(list, list + tail - 1, comp);
    int pos;
    for (int i = 0; i < tail; ++i) {
        if (i == 0) {
            res += list[i].size();
            continue;
        }
        pos = 0;
        while (list[i][pos] == list[i - 1][pos] && pos < list[i].size()) {
            ++pos;
        }
        res += list[i].size() - pos;
    }
    cout << ++res;

    return 0;
}