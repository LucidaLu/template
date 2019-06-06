typedef long long LL;

const int XN = (1 << 19) + 31, P = 1000000007;
const double PI2 = 2 * 3.141592653589793238462643383279;
int N = 1 << 19, L = 15, K = (1 << L) - 1;

struct X {
    double x, y;

    X() {}
    X(double _x, double _y) : x(_x), y(_y) {}

    X operator+(const X &z) const { return X(x + z.x, y + z.y); }

    X operator-(const X &z) const { return X(x - z.x, y - z.y); }

    X operator*(const X &z) const { return X(x * z.x - y * z.y, x * z.y + y * z.x); }

    X conj() const { return X(x, -y); }
} w[XN];

void init() {
    for (int i = 0; i < N; i++) w[i] = X(cos(PI2 / N * i), sin(PI2 / N * i));
}

void trans(int n, X x[], bool f) {
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j)
            std::swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for (int i = 2; i <= n; i <<= 1) {
        int l = i >> 1, d = N / i;
        for (int j = 0; j != n; j += i)
            for (int k = 0; k != l; k++) {
                X &a = x[j + k], &b = x[j + k + l], t = w[d * k] * b;
                b = a - t;
                a = a + t;
            }
    }
    if (!f) {
        std::reverse(x + 1, x + n);
        for (int i = 0; i < n; i++) x[i].x /= n, x[i].y /= n;
    }
}

void conv(int na, int a[], int nb, int b[], int nc, int c[]) {
    int n = 1;
    static X x[XN], y[XN], z[XN], w[XN];
    while (n < na + nb - 1) n <<= 1;
    for (int i = 0; i < n; i++) {
        x[i] = i < na ? X(a[i] & K, a[i] >> L) : X(0, 0);
        y[i] = i < nb ? X(b[i] & K, b[i] >> L) : X(0, 0);
    }
    trans(n, x, 1);
    trans(n, y, 1);
    X r0(0.5, 0), r1(0, -0.5), r(0, 1);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
        X x0 = (x[i] + x[j].conj()) * r0;
        X x1 = (x[i] - x[j].conj()) * r1;
        X y0 = (y[i] + y[j].conj()) * r0;
        X y1 = (y[i] - y[j].conj()) * r1;
        z[i] = x0 * (y0 + y1 * r);
        w[i] = x1 * (y0 + y1 * r);
    }
    trans(n, z, 0);
    trans(n, w, 0);
    for (int i = 0; i < nc; i++) {
        int c00 = (LL)(z[i].x + 0.5) % P, c01 = (LL)(z[i].y + 0.5) % P;
        int c10 = (LL)(w[i].x + 0.5) % P, c11 = (LL)(w[i].y + 0.5) % P;
        c[i] = ((((LL)c11 << L) + c01 + c10 << L) + c00) % P;
    }
}

void inv(int n, int f[], int g[]) {
    if (n == 1)
        g[0] = 1;
    else {
        int l = n + 1 >> 1;
        static int t[XN];
        inv(l, f, g);
        conv(n, f, l, g, n, t), conv(l, g, n - l, t + l, n - l, g + l);
        for (int i = l; i < n; i++)
            if (g[i])
                g[i] = P - g[i];
    }
}

int qpow(int a, int b) {
    int c = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            c = (LL)c * a % P;
        a = (LL)a * a % P;
    }
    return c;
}

int inv(int x) { return qpow(x, P - 2); }

int z[XN];

inline void ln(int n, int f[], int g[]) {
    static int t[XN];
    inv(n, f, t);
    for (int i = 1; i < n; i++) g[i - 1] = (LL)i * f[i] % P;
    g[n - 1] = 0;
    conv(n, t, n, g, n, t);
    for (int i = n - 1; i; i--) g[i] = (LL)t[i - 1] * z[i] % P;
    g[0] = 0;
}

inline void exp(int n, int f[], int g[]) {
    if (n == 1) {
        g[0] = 1;
        return;
    }
    static int t[XN];
    int l = n + 1 >> 1;
    exp(l, f, g);
    ln(n, g, t);
    for (int i = 0; i < n; i++) t[i] = (f[i] + P - t[i]) % P;
    t[0]++;
    conv(n, g, n, t, n, g);
}

int f[XN], g[XN];
int n = 0, k = 0;

int main() {
    init();
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) z[i] = inv(i);
    for (int i = 1; i <= k; i++) f[i] = (LL)z[i] * (n - 1) % P;
    for (int i = 2; i <= n; i++)
        for (int j = 1; i * j <= k; j++) f[i * j] = (f[i * j] + P - z[j]) % P;
    exp(k + 1, f, g);
    printf("%d\n", g[k]);
    return 0;
}
