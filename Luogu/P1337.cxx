#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>

using ldouble = long double;
using std::cin;
using std::cout;

std::random_device sd;
std::mt19937 rd(sd());

#define N 1005
#define endl '\n'

struct elem {
    ldouble x;
    ldouble y;
    ldouble g;
} table[N];

int n;
const ldouble DOWN = 0.995;
ldouble ansx, ansy, ansg;

ldouble energy(ldouble x, ldouble y) {
    ldouble res = 0;
    ldouble tmpx, tmpy;
    for (int i = 1; i <= n; ++i) {
        tmpx = x - table[i].x;
        tmpy = y - table[i].y;
        res += sqrt(tmpx * tmpx + tmpy * tmpy) * table[i].g;  // 两点距离公式
    }
    return res;
}

void sa() {
    ldouble temp = 3000; // 初温
    ldouble ex, ey, eg;
    ldouble cha;
    while (temp > 1e-30) {
        ex = ((long long)INT_MAX -  (long long)rd()) * temp + ansx;
        ey = ((long long)INT_MAX -  (long long)rd()) * temp + ansy;
        eg = energy(ex, ey);
        cha = eg - ansg;
        if (cha < 0) {
            ansx = ex;
            ansy = ey;
            ansg = eg;
        } else if (exp(-cha / temp) * INT_MAX > rd()) {
            ansx = ex;
            ansy = ey;
        }
        temp *= DOWN;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> table[i].x >> table[i].y >> table[i].g;
        ansx += table[i].x;
        ansy += table[i].y;
        ansg += table[i].g;
    }
    ansx /= n;
    ansy /= n;
    ansg = energy(ansx, ansy);

    sa();
    
    cout << std::fixed << std::setprecision(3) << ansx << ' ' << ansy << endl;

    return 0;
}