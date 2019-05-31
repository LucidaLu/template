// $n^n$最左边一位数
int leftmost(int n) {
	double m = n * log10((double)n);
	double g = m - (long long)m;
	g = pow(10.0, g);
	return (int)g;
}

// $n!$位数
int count(ll n) {
	return n == 1 ? 1 : (int)ceil(0.5 * log10(2 * M_PI * n) + n * log10(n) - n * log10(M_E));
}

