#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,fma,sse4.1,sse4.2,bmi,bmi2,abm,sse2,sse3,sse4,mmx,arch=cannonlake,tune=cannonlake")
#define query(pos) (a[*lower_bound(stk + 1, stk + 1 + r, (pos))])

#define endl '\n'

using std::cin;
using std::cout;
using std::lower_bound;
using std::map;
using std::string;
using std::upper_bound;

constexpr long long N = 6e5 + 514;
constexpr long long mask = (1 << 30) - 1;
long long nxt[N], anc[N];
string s;
long long a[N];    // 串和 w 数组
long long stk[N];  // 单调栈
long long r;       // 栈顶
__int128 ans, sum;
long long tmp1, tmp2;  // tmp for output
long long n;
char c;
map<long long, long long> cnt;
long long v, ncnt;

void output(__int128 out) {
    std::ios::sync_with_stdio(false);
    cout.tie(nullptr);
    constexpr long long P = 1e18;
    if (out < P) {
        cout << (long long)out << endl;
    } else {
        tmp1 = out / P, tmp2 = out % P;
        cout << tmp1 << std::setw(18) << std::setfill('0') << tmp2 << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    s.reserve(n + 1);
    cin >> c >> a[0];
    s += c;      // 第一次加字符不需要加密
    ans = a[0];  // 第一次加数字同理
    stk[++r] = 0;
    cout << a[0] << endl;  // 因此直接输出就行了

    for (long long i = 1, j = 0; i < n; ++i) {
        cin >> c >> a[i];
        c = (c - 'a' + ans % 26) % 26 + 'a';
        s += c;                      // 字符加密
        a[i] = a[i] ^ (ans & mask);  // 数字加密

        /*
            KMP
            求最长 border 肯定得 KMP 来
        */
        while (j && c != s[j]) {
            j = nxt[j];
        }
        if (s[j] == c) {
            ++j;
        }
        nxt[i + 1] = j;

        /*
            个人认为比较难理解的地方

           对于当前位置 i，因为前面的所有部分都已经考虑过了，保证正确，所以只需要处理新添加 s[i] 字符后出现的 border。
           为了保证效率，我们实际上维护了一个集合，存放的是合法的以 i 为结尾的 border，而到第二个字符 i+1 时，跳 border （i = nxt[i]，即枚举 border 的 border） 寻找是否有 border 在添加字符 s[j]
           之后不再合法并删除。 由于最多加入 n 个 border，所以每次操作删除的 border 个数是均摊 O(1) 的。 显然朴素方法删除 border 也很慢，所以这里我们维护了另一个列表 anc。 anc[i] 表示 i-1 的合法
           border 中，第一个（最长的）后一位字符与 s[i] 不相同的 border 的后一位字符。（有点绕，不理解建议多读几遍） 换种说法，就是 kmp 暴力枚举 border
           时的失败的失配指针，或者原题解说的“对每一个节点记录其第一个后继字符不一样的祖先”。 总之，这样我们就能 O(1) 时间内找到需要删除的 border。
        */
        if (c == s[nxt[i]]) {
            anc[i] = anc[nxt[i]];
        } else {
            anc[i] = nxt[i];
        }

        for (long long k = i; k > 0;) {
            if (s[k] == c) {
                k = anc[k];
            } else {
                v = query(i - k);
                --cnt[v];
                sum -= v;
                if (cnt[v] == 0) {
                    cnt.erase(v);
                }
                k = nxt[k];
            }
        }
        if (s[0] == c) {
            ++cnt[a[i]];
            sum += a[i];
        }

        /*
            单调栈
            此处单调栈维护的是权值，即 w[i]
            作用是寻找要删除的 border 区间最小 w[i]（单调栈 + 二分）
        */
        while (r && a[i] <= a[stk[r]]) {
            --r;
        }
        stk[++r] = i;

        /*
            此处 map 中元素 <a,b> 代表权值为 a 的 border 有 b 个，用来暴力找到所有大于 w[i]​ 的权值
        */
        ncnt = 0;  // 当前节点 border 的数量
        for (auto it = cnt.upper_bound(a[i]);;) {
            if (it == cnt.end()) break;
            sum -= (it->first - a[i]) * it->second;
            ncnt += it->second;
            auto j = std::next(it);
            cnt.erase(it);
            it = j;
        }
        cnt[a[i]] += ncnt;         // 记录每一个节点的 border 数量
        ans += (a[stk[1]] + sum);  // a[stk[1]] 实际上是整个串自身的最小权值，因为前面维护的是单调栈，栈底就是目前的最小权值
        output(ans);
    }

    return 0;
}