#include "SHA256.h"

uint rightRotate(uint val, int n) {
	return (val << (32 - n) | (val >> n));
}

void SHA256(char *s, uint *sha256) {
	uint hs[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
	uint w[100];
	vector<int> bin;
	int n = strlen(s);
	//信息预处理
	while (s[n - 1] == 10) s[n--] = 0;//去掉末尾换行符
	for (int i = 0; i < n; ++i) {
		for (int j = 7; j >= 0; --j)
			if (s[i] & (1 << j))
				bin.pb(1);
			else bin.pb(0);
	}
	//附加填充比特
	bin.pb(1);
	while (bin.size() % 512 != 448)
		bin.pb(0);
	//附加长度值
	LL sumLen = n * 8;
	for (int j = 63; j >= 0; --j)
		if (sumLen & (1ll << j))
			bin.pb(1);
		else bin.pb(0);
		
	assert(bin.size() % 512 == 0);
	//计算哈希值
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
		sha256[i] = hs[i];
}

