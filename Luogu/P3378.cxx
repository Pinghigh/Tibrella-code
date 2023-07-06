#pragma GCC target("avx2,sse4a,lzcnt,popcnt")

#include <cstdio>

namespace Fastio {
    namespace Fread {
        const unsigned int SIZE = (1 << 21);
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
        const unsigned int SIZE = (1 << 21);
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
// #ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
    // #endif
    struct Reader {
        template <typename T>
        Reader& operator>>(T& x) {
            static char c;
            do {
                c = getchar();
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    static char sta[111];
    char top = 0;
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            while (x)
                sta[++top] = x % 10 ^ 48, x /= 10;
            while (top)
                putchar(sta[top]), --top;
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

// #include <queue>

using namespace std;

#define N 10000100
#define min(a,b) (tree[a]<tree[b]?(a):(b))

int tree[N], tsize;
int n;

void qswap(int& a, int& b) {
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
//     cout << "[swap] " << tmp << ' ' << a << endl;
}

void ins(int a) {
    tree[++tsize] = a;
    int now, nex;
    now = tsize;    
    while (now > 1) {
    	nex = now >> 1;
        if (tree[now] >= tree[nex]) {
            break;
        }
        qswap(tree[now], tree[nex]);
        now = nex;
        
    }
//     cout << "[insert] " << a << " size: " << tsize << " pos: " << now << endl;
}

void del() {
//    cout << "[delete] " << tree[1] << endl;
    tree[1] = tree[tsize --];
    
    int now, nex;
    now = 1;
    while ((now << 1) <= (tsize)) {
        nex = now << 1;
        nex = (nex>=tsize)?nex:min(nex,nex+1); // 此处 min 输入返回的都是下标
        if (tree[now] <= tree[nex]) break;
		qswap(tree[now],tree[nex]);
        now = nex;
//        cout << "now_____" << now << endl;
        
    }
//    tsize --;
}

int main() {
	// freopen("P3378_4.in","r",stdin); freopen("out.txt","w",stdout);
    tree[0] = 0x3f3f3f3f;

    int n;
    int beh,dat;
    cin >> n;
    while(n --) {
//         cout << "---" << n << endl;
        cin >> beh;
        switch (beh) {
            case(1):
                cin >> dat;
                ins(dat);
                break;
            case(2):
                cout << tree[1] << endl;
                break;
            case(3):
                del();
                break;
        }
//        cout << "data ";
//        for (int i = 1; i <= tsize; i ++) cout << tree[i] << ' ';
//        cout << endl;
    }

    return 0;
}