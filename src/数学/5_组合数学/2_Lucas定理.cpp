// $1 \leq n, m \leq 10^9, 1 < p < 10^5$, p是素数
const int maxp = 100010;
ll f[maxp];
void CalFact(ll p) {
	f[0] = 1;
	for (int i = 1; i <= p; i++)
		f[i] = (f[i - 1] * i) % p;
}
ll Lucas(ll n, ll m, ll p) {
	ll ret = 1;
	while (n && m) {
		ll a = n % p, b = m % p;
		if (a < b) return 0;
		ret = (ret * f[a] * Pow(f[b] * f[a - b] % p, p - 2, p)) % p;
		n /= p; m /= p;
	}
	return ret;
}
