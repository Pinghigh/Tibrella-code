#ifdef TIKOGASA
#include <iostream>
#endif


template<typename T>
static void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}

using i32 = int;

int findSample(i32 n, i32* conf, i32* host, i32* prot) {
    i32& ans = *host;
    ans = 0;

    while (--n) 
        if (!prot[n]) ans += conf[n], chkmax(conf[host[n]] -= conf[n], 0);
        else if (prot[n] == 1) conf[host[n]] += conf[n];
        else chkmax(conf[host[n]], conf[n]);
    
    return ans += conf[0];
}

#ifdef TIKOGASA
#define N 100001
int n, c[N], ho[N], pro[N];
using std::cin;
using std::cout;
int main() {    
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> c[i];
    for (int i = 1; i < n; ++ i) cin >> ho[i] >> pro[i];
    cout << findSample(n, c, ho, pro);
    return 0;
}
#endif