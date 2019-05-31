// 函数返回素因数个数
// 数组以$fact[i][0]^{fact[i][1]}$的形式保存第i个素因数
ll fact[100][2];
int getFactors(ll x) {
	int cnt = 0;
	for (int i = 0; prime[i] <= x / prime[i]; i++) {
		fact[cnt][1] = 0;
		if (x % prime[i] == 0 ) {
			fact[cnt][0] = prime[i];
			while (x % prime[i] == 0) {
				fact[cnt][1]++;
				x /= prime[i];
			}
			cnt++;
		}
	}
	if (x != 1) {
		fact[cnt][0] = x;
		fact[cnt++][1] = 1;
	}
	return cnt;
}
