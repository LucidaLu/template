// 利用exgcd求a在模m下的逆元，需要保证gcd(a, m) == 1.
ll inv(ll a, ll m) {
	ll x, y, d; exgcd(a, m, d, x, y);
	return d == 1 ? (x + m) % m : -1;
}
// a < m 且 m为素数时，有以下两种求法
ll inv(ll a, ll m) {
	return a == 1 ? 1 : inv(m % a, m) * (m - m / a) % m;
} 
ll inv(ll a, ll m) {
	return Pow(a, m - 2, m);
}
