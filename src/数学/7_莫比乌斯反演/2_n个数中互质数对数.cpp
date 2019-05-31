//  有n个数（$n\leq 10^5$），问这n个数中互质的数的对数
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
long long ans;
const int MAXN = 1e5 + 1;
int n, x, prime[MAXN], _max, b[MAXN], tot, mu[MAXN];
bool check[MAXN];
void calmu() {
	mu[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (!check[i]) {
			prime[tot++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < tot; j++) {
			if (i * prime[j] >= MAXN) break;
			check[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}
int main() {
	calmu();
	while (scanf("%d", &n) == 1) {
		memset(b, 0, sizeof(b));
		_max = 0; ans = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (x > _max) _max = x;
			b[x]++;
		}
		int cnt;
		for (int i = 1; i <= _max; i++) {
			cnt = 0;
			for (long long j = i; j <= _max; j += i)
				cnt += b[j];
			ans += 1LL * mu[i] * cnt * cnt;
		}
		printf("%lld\n", (ans - b[1]) / 2);
	}
	return 0;
}
