#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define uc unsigned char
using namespace std;
const int maxn = 1e6 + 10;

struct RSA{
	vector<int> vec;
	void print() {
		for (auto x : vec)
			printf("%d ", x);
		printf("\n");
	}
};
RSA RSA_generate_key();
int i2d_RSAPublicKey(RSA rsa, unsigned char *pk);
RSA d2i_RSAPublicKey(uc *pk, int len);
void RSA_private_decrypt(int len, const uc *from, char *to);
#endif
