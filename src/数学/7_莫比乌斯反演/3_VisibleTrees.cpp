// gcd(x,y)==1的对数 $x \leq n, y \leq m$
int main() {
    calmu();
    int n, m;
    scanf("%d %d", &n, &m);
    if (n < m) swap(n, m);
    ll ans = 0;
    for (int i = 1; i <= m; ++i) {
        ans += (ll)mu[i] * (n / i) * (m / i);
    }
    printf("%lld\n", ans);
    return 0;
}
