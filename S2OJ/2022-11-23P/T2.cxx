#include <iostream>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

#define MAXN 1000010
#define MAXM 200010

int t,n,del;
set<int> avi;
bitset<MAXN> st;
bool flag;
int nums[MAXM];


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> t;

    while (t--) {
        memset(nums,0,sizeof nums);
        nums[0]=114514;
        st.reset();
        flag=1;
        avi.clear();
        auto it = avi.begin();

        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> nums[i];
            if (nums[i] != 0) {
                st[nums[i]] = 1;
            }
        }
        for (int i = 1; i <= n; i ++) {
            if (!st[i]) avi.insert(i);
        }
        
        if (avi.empty()) {
            for (int i = 1; i <= n; i ++) {
                if (nums[i] > nums[i+1]) {
                    del=nums[i];
                    break;
                }
            }
        } else {
            for (int i = 1; i <= n; i ++) {
                if (!st[i]) {
                    if (flag) {
                        if (*avi.begin() < nums[i-1]) {
                            avi.insert(nums[i-1]);
                            del=nums[i-1];
                            flag=0;
                        } else {
                            int minn=0;
                            for (int j = i; j <= n; j ++) {
                                minn=(nums[i]<nums[minn])?i:minn;
                            }
                            avi.insert(nums[minn]);
                            del=nums[minn];
                            flag=0;
                        }
                    }
                    it = avi.begin();
                    nums[i]=*it;
                    avi.erase(it);
                } else if (flag) {
                    if (nums[i] < nums[i-1]) {
                        del = nums[i-1];
                        avi.insert(nums[i-1]);
                        flag=0;
                    }
                }
            }
        }
        

        for (int i = 1; i <= n; i ++) {
            if (nums[i] != del) cout << nums[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}
