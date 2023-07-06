#include <iostream>

using std::cin;
using std::cout;

int n;
int las, a;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> a;
        if (las) {
            if (a > las && a - las > 1) {
                for (int i = las + 1; i < a; ++i)
                    cout << i << ' ';
            } else if (a < las && las - a > 1) {
                for (int i = las - 1; i > a; --i)
                    cout << i << ' ';
            }
        }
        las = a;
        cout << a << ' ';
    }
    cout << '\n';

    return 0;
}