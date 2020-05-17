#include<bits/stdc++.h>
#define pb push_back
#define LL long long
#define uint unsigned int
using namespace std;
const int maxn = 1e3 + 10;
uint w[100];
uint hs[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
const uint k[] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };
vector<int> bin;
char s[maxn];
int n;

uint rightRotate(uint val, int n) {
	return (val << (32 - n) | (val >> n));
}

int main()
{
	freopen("test.txt", "r", stdin);
	fgets(s, 10000, stdin); n = strlen(s);
	for (int i = 0; i < n; ++i) {
		for (int j = 7; j >= 0; --j)
			if (s[i] & (1 << j))
				bin.pb(1);
			else bin.pb(0);
	}
	bin.pb(1);
	while (bin.size() % 512 != 448)
		bin.pb(0);
	LL sumLen = n * 8;
	for (int j = 63; j >= 0; --j)
		if (sumLen & (1ll << j))
			bin.pb(1);
		else bin.pb(0);
		
	assert(bin.size() % 512 == 0);
	
	uint s0, s1, maj, t1, t2, ch;
	int blockNum = bin.size() / 512;
	for (int blk = 1, st = 0; blk <= blockNum; ++blk) {
		for (int i = 0; i <= 15; ++i) {
			w[i] = 0;
			for (int j = 31; j >= 0; --j) if (bin[st++]) {
				w[i] |= (1u << j);
			}
		}
		for (int i = 16; i <= 63; ++i) {
			s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
			s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		}
		uint a = hs[0], b = hs[1], c = hs[2], d = hs[3], e = hs[4], f = hs[5], g = hs[6], h = hs[7];
		for (int i = 0; i <= 63; ++i) {
			s0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
			maj = (a & b) ^ (a & c) ^ (b & c);
			t2 = s0 + maj;
			s1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
			ch = (e & f) ^ ((~ e) & g);
			t1 = h + s1 + ch + k[i] + w[i];
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}
		hs[0] += a; hs[1] += b; hs[2] += c; hs[3] += d;
		hs[4] += e; hs[5] += f; hs[6] += g; hs[7] += h;
	}
	for (int i = 0; i < 8; ++i)
		printf("%08x", hs[i]);
	return 0;
}

