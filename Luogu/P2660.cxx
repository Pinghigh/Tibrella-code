#include <cstdio>
// #include <cctype>
#define ll long long
// #define SIZE (1 << 21)
// #define Getchar() (pr1 == pr2 && (pr2 = (pr1 = fr) + fread(fr, 1, SIZE, stdin), pr1 == pr2) ? EOF : *pr1++)
// #define putchar(ch) (pw < SIZE ? fw[pw++] = (ch) : (fwrite(fw, 1, SIZE, stdout), fw[(pw = 0)++] = (ch)))
// char fr[SIZE], * pr1 = fr, * pr2 = fr;
// char fw[SIZE];
ll int pw;
// ll int rd() {
//     ll int k = 0;
//     char c = getchar();
//     while (c < '0' || c > '9')
//         c = getchar();
//     while (c >= '0' && c <= '9') {
//         k = (k << 1) + (k << 3) + (c ^ 48);
//         c = getchar();
//     }
//     return k;
// }
// void wr(const ll int x) {
//     if (x > 9)wr(x / 10);
//     putchar(x % 10 + '0');
// }
namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 21);
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
        const int SIZE = (1 << 21);
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
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            T dp = 1;
            while (c < '0' || c > '9') {
                if (c == '-') dp = -1;
                c = getchar();
            }
            x = 0;
            while (c >= '0' && c <= '9')
                x = x * 10 + (c - '0'), c = getchar();
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& c) {
            c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            char c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            if (x < 0) putchar('-'), x = -x;
            static int sta[111];
            int top = 0;
            while (x)
                sta[++top] = x % 10, x /= 10;
            while (top)
                putchar(sta[top] + '0'), --top;
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
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace std;
ll int pay, a, b, r;
int main() {
    cin >> a >> b;
    for (; b != 0 && a != 0;) {
        if (a <= b) {
            r = b / a;
            pay += 4 * a * r;
            b -= r * a;
            // cout << a << ' ' << b << endl;
        } else if (a > b) {
            // cout << a << ' ' << b << endl;
            r = a / b;
            pay += 4 * b * r;
            a -= r * b;
        }
    }
    // printf("%lld",pay);
    // wr(pay);
    cout << pay;
    return 0;
}