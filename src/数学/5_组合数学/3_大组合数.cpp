// $0 \leq n \leq 10^9, 0 \leq m \leq 10^4, 1 \leq k \leq 10^9+7$
vector<int> v;
int dp[110];
ll Cal(int l, int r, int k, int dis) {
	ll res = 1;
	for (int i = l; i <= r; i++) {
		int t = i;
		for (int j = 0; j < v.size(); j++) {
			int y = v[j];
			while (t % y == 0) {
				dp[j] += dis;
				t /= y;
			}
		}
		res = res * (ll)t % k;
	}
	return res;
}
ll Comb(int n, int m, int k) {
	set(dp, 0); v.clear(); int tmp = k;
	for (int i = 2; i * i <= tmp; i++) {
		if (tmp % i == 0) {
			int num = 0;
			while (tmp % i == 0) {
				tmp /= i;
				num++;
			}
			v.pb(i);
		}
	} if (tmp != 1) v.pb(tmp);
	ll ans = Cal(n - m + 1, n, k, 1);
	for (int j = 0; j < v.size(); j++) {
		ans = ans * Pow(v[j], dp[j], k) % k;
	}
	ans = ans * inv(Cal(2, m, k, -1), k) % k;
	return ans;
}
