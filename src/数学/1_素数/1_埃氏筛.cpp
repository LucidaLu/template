// $O(n\log\log n)$筛出MAXN内所有素数
// $notprime[i] = 0/1$ 0为素数 1为非素数
const int MAXN = 1000100;
bool notprime[MAXN] = {1, 1};	// 0/1 为非素数
void GetPrime() {
	for (int i = 2; i < MAXN; i++)
		if (!notprime[i] && i <= MAXN / i)	// 筛到√n为止
			for (int j = i * i; j < MAXN; j += i)
				notprime[j] = 1;
}
