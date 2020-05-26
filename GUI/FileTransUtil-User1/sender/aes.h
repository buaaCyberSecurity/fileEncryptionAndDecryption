#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED
#include <stdio.h>
#include <string.h>
//encrypt 16bytes
void AesEncrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);
//encrypt 256bytes
void Aes_256_encrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);
//contrary encrypt 16bytes
void Contrary_AesEncrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);
//contrary encrypt 256bytes
void Contrary_256_AesEncrypt(unsigned char *blk,unsigned char *expansionkey,int Nr);
//get AES expansionKey
void ScheduleKey(unsigned char *inkey,unsigned char *outkey,int Nk,int Nr);
#endif // AES_H_INCLUDED