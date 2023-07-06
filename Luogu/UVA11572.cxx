#include <stdio.h>
#include <map>

using namespace std;

int sn,max,sum,T,c,last,res;
map<int,int> snows;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    while (T --) {
        cin >> c;
        snows.clear();
        last = res = 0;

        for (int i = 1; i <= c; i ++) {
            cin >> sn;
            if (snow[sn] > last) last = snow[sn];
            res=max(res,i-last);
            snow[sn] = i;
        }

    }

    return 0;
}