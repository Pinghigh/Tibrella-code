#include <iostream>
#include <algorithm>

using namespace std;

#define N 3000

int em[N], self[N];
int* eh=NULL; int* sh=NULL;
int* et=NULL; int* st=NULL;
int ans;
int n,tmp;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> self[i];
    }
    for (int i = 0; i < n; ++ i) {
        cin >> em[i];
    } 

    sort(self,self + n); sort(em, em + n);
    et=em+n-1, st=self+n-1;
    eh=em; sh=self;

    while (sh <= st) {
        if (*st > *et) {
            ans += 200;
            et --; st --;
        } else {
            if (*sh > *eh) {
                ans += 200;
                sh ++; eh ++;
            } else if (*sh < *et) {
                ans -= 200;
                sh ++; et --;
            } else if (*sh==*et) {
                sh ++ ; et --;
            }
        }

        // if (*eh >= *sh) {
        //     // cout << *sh << ' ' << *eh << endl;
        //     if (*sh==*et) {
        //         sh ++; et --;
        //     } else {
        //         sh ++; et --;
        //         ans -= 200;
        //     }
        // }
        
    }

    cout << ans;

    return 0;
}
