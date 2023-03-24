#include <iostream>
#include <cstring>

#define N 305;
#define endl '\n'
#define cin std::cin
#define cout std::cout

struct edge {
    edge* nex;
    int from, to;
} graph[N];

int n,m;
int val[N];
int t1;

int main() {
    std::ios::sync_wiht_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        cin >> t1 >> val[i]; 
    }
    
    return 0;
}