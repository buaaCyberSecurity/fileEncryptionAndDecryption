#ifndef SENDER_H_INCLUDED
#define SENDER_H_INCLUDED
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
//sendKey: take rsa public key,public key length,client sock as inputs. Send rsa public key to receiver.
int sendKey(unsigned char *pk,int pk_len,int clnt_sock);
//sendData: take data after aes encryption, data length,client sock as inputs. Send data after aes encryption to receiver.
int sendData(unsigned char *data,int d_len,int clnt_sock);
//send file
int sendFile(FILE* fp,unsigned long fsize,unsigned char *path,unsigned char *data_to_encrypt,unsigned char *data_after_encrypt,AES_KEY *AESEncryptKey,int clnt_sock);
//recvSeed: take buffer, length of the data to receive, client sock as inputs. Receive seed to generate aes key from receiver.
int recvSeed(unsigned char *buffer,int s_len,int clnt_sock);
//create server socket.
int getServerSocket(const char *ip,int port);
//waiting for connection from receiver.
int waitForConnection(int serv_sock);



#endif // SENDER_H_INCLUDED
