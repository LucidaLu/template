// $X = r[i] % m[i]$, 要求m[i]两两互质
// 引用返回通解$X = re + k * mo$
void crt(ll r[], ll m[], ll n, ll &re, ll &mo) {
	mo = 1, re = 0;
	for (int i = 0; i < n; i++) mo *= m[i];
	for (int i = 0; i < n; i++) {
		ll x, y, d, tm = mo / m[i];
		exgcd(tm, m[i], d, x, y);
		re = (re + tm * x * r[i]) % mo;
	} re = (re + mo) % mo;
}
