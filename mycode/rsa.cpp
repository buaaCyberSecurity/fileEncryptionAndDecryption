#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define uc unsigned char
using namespace std;
const int maxn = 1e6 + 10;
vector<int> vec;
uc encode[maxn * 4];
int n, phi_n, encodelen;
int d, e, p, q, cnt, vis[maxn], pri[maxn];

void getPrime(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) pri[++cnt] = i;
		for (int j = 1; j <= cnt && i * pri[j] <= n; ++j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

int phi(int n) {
	int ret = 1;
	for (int i = 1, num, pro; i <= cnt; ++i) {
		num = 0; pro = 1;
		while (n % pri[i] == 0) {
			++num;
			pro *= pri[i];
			n /= pri[i];
		}
		ret *= (pro - pro / pri[i]);
	}
	return ret;
}

int qpow(int a, int b, int mod) {
	if (!b) return 1;
	int ret = qpow(a, b / 2, mod);
	ret = 1ll * ret * ret % mod;
	if (b & 1) ret = 1ll * ret * a % mod;
	return ret;
}
char plainText[maxn], decode[maxn];

void print0x(uc *s, int len) {
	for (int i = 0; i < len; ++i)
		printf("0x%02x ", s[i]);
	puts("");
}

void enCode(char *from, uc *to, int &tolen) {
	int len = strlen(from);
	for (int i = 0, c; i < len; ++i) {
		c = qpow(from[i], e, n);
		to[tolen++] = (c >> 24);
		to[tolen++] = ((c >> 16) & 0xff);
		to[tolen++] = ((c >> 8) & 0xff);
		to[tolen++] = (c & 0xff);
	}
}

void deCode(uc *from, char *to, int len) {
	for (int i = 0, x; i < len; i += 4) {
		x = 0;
		for (int j = 0; j < 4; ++j) {
			x <<= 8;
			x |= from[i + j];
		}
		*(to++) = qpow(x, d, n);
	}
}

int main()
{
	freopen("test.txt", "r", stdin);
	
	srand(time(0));
	getPrime(1000);
	
	p = pri[rand() % (cnt - 10) + 11];
	q = pri[rand() % (cnt - 10) + 11];
	while (p == q) q = pri[rand() % cnt + 1];
	
	n = p * q;
	
	phi_n = (p - 1) * (q - 1);
	
	for (int i = 11; i <= cnt; ++i)
		if (pri[i] < phi_n && phi_n % pri[i] != 0)
			vec.pb(pri[i]);

	e = vec[rand() % vec.size()];
	
	d = qpow(e, phi(phi_n) - 1, phi_n);
	
	fgets(plainText, 1000000, stdin);
	
	enCode(plainText, encode, encodelen);
	
	deCode(encode, decode, encodelen);
	
	printf("%s", decode);
	
	return 0;
}
