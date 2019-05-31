// 引用返回通解: $X = x + k * dx, Y = y – k * dy$
// 引用返回的x是最小非负整数解，方程无解函数返回0
#define Mod(a,b) (((a)%(b)+(b))%(b))
bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy) {
	if (a == 0 && b == 0) return 0;
	ll d, x0, y0; exgcd(a, b, d, x0, y0);
	if (c % d != 0) return 0;
	dx = b / d; dy = a / d;
	x = Mod(x0 * c / d, dx); y = (c - a * x) / b; 
// y = Mod(y0 * c / d, dy); x = (c - b * y) / a;
	return 1;
}
