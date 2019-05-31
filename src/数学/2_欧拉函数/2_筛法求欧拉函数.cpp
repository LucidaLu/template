const int N = 10001;
int phi[N] = {0, 1};
void CalEuler() {
	for (int i = 2; i < N; i++)
		if (!phi[i]) for (int j = i; j < N; j += i) {
				if (!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
}
