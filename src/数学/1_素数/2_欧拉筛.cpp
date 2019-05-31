// $O(n)$得到欧拉函数$phi[]$、素数表$prime[]$、素数个数$tot$
// 传入的n为函数定义域上界
const int MAXN = 100010;
bool vis[MAXN];
int tot, phi[MAXN], prime[MAXN];
void CalPhi(int n) {
	set(vis, 0); phi[1] = 1; tot = 0;
	for (int i = 2; i < n; i++) {
		if (!vis[i]) {
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0; j < tot; j++) {
			if (i * prime[j] > n) break;
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}
