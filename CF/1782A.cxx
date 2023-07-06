#include <iostream>
#include <cmath>

using namespace std;

// #define abs(a) ((a) < 0 ? -(a) : (a))
#define max(a, b) ((a) < (b) ? (b) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))

struct node {
    int x, y;
};

int w, d, h;        // 长宽高
node laptop, projector;  // laptop and projector
int res;
int t;           // test cases
int w1,w2,w3,w4;

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cin >> t;
    while (t--) {
        cin >> w >> d >> h >> laptop.x >> laptop.y >> projector.x >> projector.y;

        w1 = (w*2)-laptop.x-projector.x+abs(laptop.y-projector.y)+h;
        w2 = (d*2)-laptop.y-projector.y+abs(laptop.x-projector.x)+h;
        w3 = laptop.y+projector.y+abs(laptop.x-projector.x)+h;
        w4 = laptop.x+projector.x+abs(laptop.y-projector.y)+h;
        cout << min(min(w1,w2),min(w3,w4)) << endl;
    }

    return 0;
}