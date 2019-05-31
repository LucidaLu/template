long long Euler(long long n) {
	long long rt = n;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			rt -= rt / i;
			while (n % i == 0) n /= i;
		}
	if (n > 1) rt -= rt / n;
	return rt;
}
