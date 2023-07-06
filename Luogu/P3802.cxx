#include <iomanip>
#include <iostream>

double a, b, c, d, e, f, g, n;

int main() {
    std::cin >> a >> b >> c >> d >> e >> f >> g;
    n = a + b + c + d + e + f + g;
    if (!a || !b || !c || !d || !e || !f || !g) return (std::cout << "0.000"), 0;
    std::cout << std::fixed << std::setprecision(3) << 5040 * (n - 6) * a / n * b / (n - 1) * c / (n - 2) * d / (n - 3) * e / (n - 4) * f / (n - 5) * g / (n - 6);
    return 0;
}