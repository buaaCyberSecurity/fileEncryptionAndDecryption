#ifndef RECEIVER_H_INCLUDED
#define RECEIVER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <openssl/rsa.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#define SEED_LEN 128
int sendSeed(unsigned char *seed,int s_len,int sock);
int recvEncryptedData(unsigned char *dae,int d_len,int sock);
int recvPKeyAndLen(unsigned char *b_f, int32_t *pk_len,int sock);
int genSeed(unsigned char* ranstr);
int recvFile(unsigned char *data_after_encrypt,unsigned char *data_after_decrypt,AES_KEY *AESDecryptKey,int sock);
#endif // RECEIVER_H_INCLUDED
