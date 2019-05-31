void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
	if (!b) {d = a; x = 1; y = 0;}
	else {exgcd(b, a % b, d, y, x); y -= x * (a / b);}
}
