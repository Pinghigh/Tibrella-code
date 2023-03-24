#pragma GCC target("avx2,sse4.2,avx512f,bmi,bmi2,mmx,popcnt,lzcnt")

#include <cstring>
#include <cstdio>
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = 1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    x *= (f ? -1 : 1);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    static short int __output_stack[64], __pos;
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos] ^ 48);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch = ' ', __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

using llint = long long int;
using sint = short int;

#define endl '\n';
#define N 13

llint l, r;
// 依次为 当前位数，上位，上上位，是否已经出现连续三个相同数字，是否有 4，是否有 8，
llint f[N][N][N][2][2][2];
short int sta[N];

// 多出来的 limit 表示是否到了边界（即最大数字

llint dfs(sint pos, sint pr, sint ppr, bool state, bool four, bool eight, bool limit) {
    if (four && eight) return 0;  // 同时出现 4 8
    if (!pos) return state;       // 到达尽头，如果之前出现过三个连续相同数字，就是一个合法的电话号码
    if (!limit && ~f[pos][pr][ppr][state][four][eight]) return f[pos][pr][ppr][state][four][eight];  // 记忆化搜索，由于不能保证同一种情况有同一个边界，所以需要判断 limit 的情况

    llint res = 0;
    sint max_num = limit ? sta[pos] : 9;

    for (int i = 0; i <= max_num; ++i) {                                                                                    // 此处枚举当前位的数字
        res += dfs(pos - 1, i, pr, state || (pr == ppr && pr == i), i == 4 || four, i == 8 || eight, limit && i == max_num);  // 这里不要忘记了原状态，即转移前的状态
    }
    if (!limit) {
        f[pos][pr][ppr][state][four][eight] = res;
    }
    return res;
}

llint solve(llint num) {
    if (num < 1e10) return 0;  // 此处特判当左边界为 1e10 的时候查找的是 999999999 以前的电话号码，显然不存在，因此特判

    sint pos = 0;
    do {
        sta[++pos] = num % 10;
        num /= 10;
    } while (num);

   

    llint ans = 0;
    // 要求电话号码没有前导 0，懒得特判，因而枚举非 0 数作为开头
    for (int i = 1; i <= sta[pos]; ++i) {
        ans += dfs(10 /* 当前要枚举的位置，而 i 已经是上一位了 */, i, 0, 0, i == 4, i == 8, i == sta[pos]);
    }

    return ans;
}

int main() {
    read(l,r); memset(f, -1, sizeof f);
    write(solve(r), solve(l-1));

    return 0;
}