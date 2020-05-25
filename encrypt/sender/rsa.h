#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
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
#endif
