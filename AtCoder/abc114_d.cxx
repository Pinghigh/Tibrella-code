#pragma GCC optimize("O3,inline")
#pragma GCC target("avx2,sse4a,bmi,bmi2,lzcnt,popcnt,fma")

#include <cstdio>

constexpr char c[][4] = { "0",   "0",   "0",   "0",   "0",   "0",   "0",   "0",   "0",   "0",   "1",   "1",   "1",   "1",   "2",   "2",   "3",   "3",   "3",   "3",   "8",
                          "8",   "11",  "11",  "11",  "11",  "14",  "14",  "32",  "32",  "35",  "35",  "35",  "35",  "42",  "42",  "42",  "42",  "49",  "49",  "49",  "49",
                          "49",  "49",  "75",  "75",  "86",  "86",  "86",  "86",  "86",  "86",  "123", "123", "131", "131", "131", "131", "148", "148", "153", "153", "170",
                          "170", "170", "170", "170", "170", "227", "227", "227", "227", "227", "227", "250", "250", "323", "323", "324", "324", "324", "324", "354", "354",
                          "354", "354", "384", "384", "384", "384", "384", "391", "491", "491", "529", "529", "529", "529", "529", "529", "543" };

unsigned char n;

int main() {
    scanf("%u", &n);
    fwrite(c[n], 1, (c[n][1] == 0 ? 1 : (c[n][2] == 0 ? 2 : 3)), stdout);
    return 0;
}

/* 
打表用的是正解..只不过数据范围太小了
#include <iostream>

using std::cin;
using std::cout;

#define N 105

using i32 = int;

i32 n, cnt[N];

void resolute(i32 x) {
    for (int i = 2; x > 1; ++i) {
        while (!(x % i)) {
            ++cnt[i];
            x /= i;
        }
    }
}

i32 count(i32 x) {
    i32 res = 0;
    for (int i = 1; i <= 97; ++i)
        res += (cnt[i] >= x);
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 1; i <= 100; ++i) {
        resolute(i);
        cout << '\"' <<  (count(74) + count(24) * (count(2) - 1) + count(14) * (count(4) - 1) + ((count(4) * (count(4) - 1) * (count(2) - 2)) >> 1)) << "\", ";
    }

    return 0;
}
*/