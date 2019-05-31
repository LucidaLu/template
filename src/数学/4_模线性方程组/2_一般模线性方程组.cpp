// $X = r[i] % m[i]$, m[i]可以不两两互质
// 引用返回通解$X = re + k * mo$, 函数返回是否有解
bool excrt(ll r[], ll m[], ll n, ll &re, ll &mo) {
	ll x, y, d; mo = m[0], re = r[0];
	for (int i = 1; i < n; i++) {
		exgcd(mo, m[i], d, x, y);
		if ((r[i] - re) % d != 0) return 0;
		x = (r[i] - re) / d * x % (m[i] / d);
		re += x * mo;
		mo = mo / d * m[i];
		re %= mo;
	} re = (re + mo) % mo;
	return 1;
}
