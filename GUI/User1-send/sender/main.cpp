#include "sender.h"
#include "string.h"
#include "aes.h"
#include "rsa.h"
//#include "SHA256.h"
const int seedEncryptLen = 127 << 2;
//char s[1000010];
//uint h[10];

int main(int argc,char *argv[]){
    int serv_sock=getServerSocket(argv[1],atoi(argv[2]));
    printf("Sender socket ready.\n");
    printf("Waiting for connection...\n");
    int clnt_sock=waitForConnection(serv_sock);
    printf("Connection built.\n");
    
    RSA ClientRSA = RSA_generate_key();
    //print the rsa.
    printf("ClientRSA is:\n");
    ClientRSA.print();
    unsigned char PublicKey[1024];
    unsigned char *PKey=PublicKey;
    //Extract the public key information into buffer. In case of changes on the PublicKey, we use pointer PKey.
    int PublicKeyLen=i2d_RSAPublicKey(ClientRSA, PublicKey);
    //print public key length, needed later.
    printf("PublicKeyBuff, Len=%d\n", PublicKeyLen);
    //print public key information for comparison
    for (int i=0; i<PublicKeyLen; i++)
    {
        printf("0x%02x ", *(PublicKey+i));
    }
    printf("\n");
    //send public key information and key length to receiver.
    sendKey(PublicKey,PublicKeyLen,clnt_sock);
    //Again, for comparison.
    PKey = PublicKey;
    RSA EncryptRsa = d2i_RSAPublicKey(PublicKey, PublicKeyLen);
    printf("You can compare this with the public key on the receiver.\n");
    EncryptRsa.print();

    //receive the encrypted seed.
    unsigned char buffer[128 << 2];
    unsigned char *s_b=buffer;
    recvSeed(s_b,seedEncryptLen,clnt_sock);
    printf("The encrypted seed is:\n");
    for (int i = 0; i < seedEncryptLen; ++i)
        printf("0x%02x ", buffer[i]);
    printf("\n");
    //decrypt the seed.
    char outseed[128];
    memset(outseed, 0, sizeof(outseed));
    RSA_private_decrypt(seedEncryptLen, (const unsigned char*)buffer, outseed);
    printf("The origin seed is %s\n",outseed);
    //aes-key
    unsigned char aesSeed[16]; //If you use no-padding while encrypting the origin seed, it must be 128bytes, but we only need the first 32bytes.
    unsigned char expansionkey[15*16];
    strncpy((char*)aesSeed,(const char*)outseed,16);
    ScheduleKey(aesSeed, expansionkey, 4, 10);
    printf("Negotiation completes.\n");
    unsigned char path[4097];
    unsigned char fname[4097];
    unsigned char data_to_encrypt[16];
    unsigned char data_after_encrypt[16];
    unsigned char *dae;
    unsigned long fsize;
    
    printf("Send file start... \n");
    FILE* fp;
    strcpy((char *)path,argv[3]);
    if((fp = fopen((const char*)path,"rb"))!=NULL){	 
        printf("File opening...\n");
        fseek(fp,SEEK_SET,SEEK_END);
        fsize=ftell(fp);	
        fseek(fp,0,SEEK_SET);
        memset(data_to_encrypt,0,sizeof(data_to_encrypt));
        sendFile(fp,fsize,path,data_to_encrypt,data_after_encrypt,expansionkey,clnt_sock);
        fclose(fp);
        //printf("\nthe sender SHA256-hash value is:\n");
        //SHA256(s, h);
        //for (int i = 0; i < 8; ++i)
        //    printf("%08x", h[i]);
        //printf("\n\n");
    }
    close(serv_sock);
    return 0;
}
