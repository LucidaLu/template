// 推论：一共$n$个置换，第$i$个置换的循环节个数为$gcd(i,n)$
// $N*N$的正方形格子，$c^{n^2}+2c^{\frac{n^2+3}{4}}+c^{\frac{n^2+1}{2}}+2c^{n\frac{n+1}{2}}+2c^{\frac{n(n+1)}{2}}$
// 正六面体，$(m^8+17m^4+6m^2)/24$
// 正四面体，$(m^4+11m^2)/12$
// 长度为n的项链串用c种颜色染
ll solve(int c, int n) {
	if (n == 0) return 0;
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += Pow(c, __gcd(i, n));
	if (n & 1)
		ans += n * Pow(c, n + 1 >> 1);
	else
		ans += n / 2 * (1 + c) * Pow(c, n >> 1);
	return ans / n / 2;
}
