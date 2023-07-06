#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdio>
#include <queue>
#include <string>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S, *T;
        inline char getchar() {
            if (S == T) {
                T = (S = buf) + fread(buf, 1, SIZE, stdin);
                if (S == T) return '\n';
            }
            return *S++;
        }
    }  // namespace Fread
    namespace Fwrite {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S = buf, *T = buf + SIZE;
        inline void flush() {
            fwrite(buf, 1, S - buf, stdout);
            S = buf;
        }
        inline void putchar(char c) {
            *S++ = c;
            if (S == T) flush();
        }
        struct NTR {
            ~NTR() {
                flush();
            }
        } ztr;
    }  // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif
    struct Reader {
        char c;
        template <typename T>
        Reader& operator>>(T& x) {
            T dp = 1;
            do {
                c = getchar();
                if (c == '-') dp = -1;
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& ch) {
            ch = getchar();
            while (ch == ' ' || ch == '\n')
                ch = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            c = getchar();
            while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        Reader& operator>>(std::string& str) {
            str.resize(0);
            do {
                c = getchar();
            } while (c == ' ' || c == '\n');
            do {
                str += c, c = getchar();
            } while (c != ' ' && c != '\n' && c != '\r');
            // str += '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    static char __output_sta[40];
    int __output_top;

#define sta __output_sta
#define top __output_top

    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (x < 0) putchar('-'), x = -x;
            top = 0;
            do {
                sta[++top] = x % 10 ^ 48, x /= 10;
            } while (x);
            do {
                putchar(sta[top--]);
            } while (top);
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        Writer& operator<<(char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const std::string& str) {
            for (auto& c : str)
                putchar(c);
            return *this;
        }
        inline Writer() {}
#undef sta
#undef top
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

using std::string;
using i32 = int;

#define N 200005

string s, t;
i32 n;

struct Node {
    i32 son[26], fail;
    i32 cnt;
} trie[N * 26];
i32 tot;
i32 end[N];
i32 stk[N], top;

void insert(string& str, i32 id) {
    i32 idx = 0;
    for (auto& c : str) {
        if (!trie[idx].son[c - 'a']) {
            trie[idx].son[c - 'a'] = ++tot;
        }
        idx = trie[idx].son[c - 'a'];
    }
    end[id] = idx;
}

void build() {
    std::queue<i32> q;
    for (i32 i = 0; i < 26; ++i)
        if (trie[0].son[i]) q.push(trie[0].son[i]);
    while (!q.empty()) {
        i32 nod = q.front(), lfail = trie[q.front()].fail;
        q.pop();
        for (i32 i = 0; i < 26; ++i) {
            i32& to = trie[nod].son[i];
            if (to) {
                trie[to].fail = trie[lfail].son[i];
                q.push(to);
            } else
                to = trie[lfail].son[i];
        }
        stk[++top] = nod;
    }
}

void match(string& str) {
    i32 nod = 0;
    for (auto c : str) {
        c -= 'a';
        nod = trie[nod].son[c];
        ++trie[nod].cnt;
    }
}

void add_up() {
    while (top) {
        i32 nod = stk[top--];
        trie[trie[nod].fail].cnt += trie[nod].cnt;
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        // cout << s << endl;
        insert(s, i);
    }

    build();

    cin >> t;

    match(t);

    add_up();

    for (int i = 1; i <= n; ++i)
        cout << trie[end[i]].cnt << endl;

    return 0;
}