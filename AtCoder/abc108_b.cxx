#include <iostream>

using std::cin;
using std::cout;

using i32 = int;

i32 a,b,c,d;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> a >> b >> c >> d;
    
    cout << c-(d-b) << ' '<< d+(c-a) << ' ' << a-(d-b) << ' ' << b+(c-a);

    return 0;
}