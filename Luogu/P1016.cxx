#include <deque>
#include <iomanip>
#include <iostream>

#pragma GCC target ("avx2,popcnt,lzcnt,fma,sse4.1,sse4.2,bmi,bmi2,abm,sse2,sse3,sse4,mmx")

using std::cin;
using std::cout;
using std::deque;

#define N 10
#define NUM 514
#define FAIL "No Solution"
#define endl '\n'

class sta {
public:
    double dis;
    double price;
} stations[N];

class oil {
public:
    double cost;
    double last;  // 油量
    oil(double val1, double val2) : cost(val1), last(val2) {}
};

double d1;    // 两个城市之间的距离
double c;     // 总容量
double d2;    // 每升汽油能行驶的距离
double p;     // 出发点汽油价格
short int n;  // 油站数量
double c_now, need;
double ans;
sta* st;

deque<oil> q;
oil now_oil(0, 0);

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> d1 >> c >> d2 >> p >> n;
    for (st = stations + 1; st <= stations + n; ++st) {
        cin >> st->dis >> st->price;
    }

    st = stations;
    st->dis = 0;
    st->price = p;
    st = stations + n + 1;
    st->dis = d1;
    st = stations;

    ans += st->price * c;
    c_now = c;
    q.push_back(oil(st->price, c));
    for (st = stations + 1; st < stations + n + 2; ++st) {
        need = (st->dis - (st - 1)->dis) / d2;
        if (need > c) {
            cout << FAIL << endl;
            return 0;
        }
        while (!q.empty() && need > 0) {
            now_oil = q.front();
            q.pop_front();
            if (now_oil.last > need) {
                now_oil.last -= need;
                q.push_front(oil(now_oil.cost, now_oil.last - need));
                break;
            }
            c_now -= now_oil.last;
            need -= now_oil.last;
        }

        while (!q.empty() && q.back().cost > st->price) {  // 物理意义上的退油
            ans -= q.back().cost * q.back().last;
            c_now -= q.back().last;
            q.pop_back();
        }

        ans += (c - c_now) * st->price;
        q.push_back(oil(st->price, c - c_now));
        c_now = c;
    }

    while (!q.empty()) {
        ans -= q.front().last * q.front().cost;
        q.pop_front();
    }

    cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << ans << endl;

    return 0;
}
