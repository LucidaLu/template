ll Mul(ll a, ll b, ll mod) {
	ll t = 0;
	for (; b; b >>= 1, a = (a << 1) % mod)
		if (b & 1) t = (t + a) % mod;
	return t;
}

ll Pow(ll a, ll n, ll mod) {
    ll t = 1;
    for (; n; n >>= 1, a = (a * a % mod))
        if (n & 1) t = (t * a % mod);
    return t;
}
