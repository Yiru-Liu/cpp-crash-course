#include <cstdio>

using ll = long long;

ll a(ll n) {
    if (n == 1) return 2;
    if (n == 2) return 5;
    return 3 * a(n - 1) - a(n - 2);
}

int main() {
    ll result = a(32);
    printf("%lld\n", result);
}
