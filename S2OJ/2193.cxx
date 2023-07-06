#include <cstdio>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

char __input_ch;
#define ch __input_ch

void read(char& c) {
    do {
        c = getchar();
    } while (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

template <typename T>
void read(T& x) {
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x), read(args...);
}

#undef ch

char __output_stk[40], __top;

#define stk __output_stk
#define top __top

template <typename T>
void write(T x) {
    do {
        stk[++top] = x % 10 ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(stk[top]);
    } while (--top);
}

template <typename T>
void write(T x, char ch) {
    write(x), putchar(ch);
}

template <typename T, typename... Args>
void write(T x, Args... args) {
    write(x), write(args...);
}

template <typename T, typename... Args>
void write(T x, char ch, Args... args) {
    write(x), putchar(ch), write(args...);
}

#include <bitset>
#include <cstdint>
#include <ext/pb_ds/priority_queue.hpp>

/*
    DEFINATION

    1. up
    2. down
    3. left
    4. right
    5. stop
*/

#define N 505

int n, m;

std::bitset<5> vis[N][N];
struct pos {
    int x, y;
    int val;
    int d;
};
int eval(const pos& a) {
    // return (a.x != n) + (a.y != m) - 1;
    if (a.x != n && a.y != m)
        return 1 + (a.d != 2 && a.d != 4);
    else if (a.x != n && a.d != 2)
        return 1;
    else if (a.y != m && a.d != 4)
        return 1;
    return 0;
}

bool operator<(const pos& exa1, const pos& exa2) {
    return exa1.val < exa2.val;
}
bool operator>(const pos& exa1, const pos& exa2) {
    return exa1.val > exa2.val;
}

__gnu_pbds::priority_queue<pos, std::greater<pos>> q;
char ch;
int mp[N][N];
int x[5] = { 0, -1, 1, 0, 0 };
int y[5] = { 0, 0, 0, -1, 1 };

bool valid(int px, int py, int d) {
    return (mp[px][py] != d && px + x[d] <= n && px + x[d] > 0 && py + y[d] <= m && py + y[d] > 0 && (mp[px + x[d]][py + y[d]] != 5 || ((px + x[d]) == n && (py + y[d]) == m))
            && !vis[px + x[d]][py + y[d]][d]);
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            read(ch);
            if (ch == 'U')
                mp[i][j] = 1;
            else if (ch == 'D')
                mp[i][j] = 2;
            else if (ch == 'L')
                mp[i][j] = 3;
            else if (ch == 'R')
                mp[i][j] = 4;
            else
                mp[i][j] = 5;
        }
    }

    for (int i = 1; i < 5; ++i)
        if (valid(1, 1, i)) q.push({ 1, 1, 0, i });

    while (!q.empty()) {
        pos now = q.top();
        vis[now.x][now.y][now.d] = true;
        // write(now.x, ' ', now.y, ' ', now.d, ' ', now.val, '\n');
        q.pop();
        if (now.x == n && now.y == m) {
            write(now.val, '\n');
            return 0;
        }
        for (int i = 1; i < 5; ++i) {
            if (valid(now.x, now.y, i)) {
                q.push((pos){ now.x + x[i], now.y + y[i], now.val + (i != now.d), i });
            }
        }
    }
    puts("No Solution");

    return 0;
}