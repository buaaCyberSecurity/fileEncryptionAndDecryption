#include "receiver.h"
#include "string.h"
#include "aes.h"
#include "rsa.h"

int main(int argc,char *argv[])
{
    //get socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //connect sender
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //ipv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //ip address
    serv_addr.sin_port = htons(atoi(argv[2]));  //port
    int result=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(result==-1){
        printf("errno for connection is %d\n",errno);
    }else{
        printf("connection built!\n");
    }
    //receive public key and key length
    unsigned char buffer[100000];
    unsigned char *b_f=buffer;
    int32_t pk_len=0;
    recvPKeyAndLen(b_f,&pk_len,sock);

    //print public key information for comparison
    for (int i=0; i<ntohl(pk_len); i++)
    {
        printf("0x%02x ", *(buffer+i));
    }
    printf("\npklen from server:%d\n",ntohl(pk_len));
    //generate public key
    RSA EncryptRsa = d2i_RSAPublicKey(buffer, (int)ntohl(pk_len));
    printf("You can compare this with the public key on the sender.\n");
    EncryptRsa.print();

    //encrypt process
    char seed[SEED_LEN];
    unsigned char outseed[SEED_LEN << 2];
    unsigned char ranstr[SEED_LEN];
    memset(ranstr,0,128);
    genSeed(ranstr);
    strcpy(seed,(const char*)ranstr);
    int l = 0;
    RSA_public_encrypt(seed, outseed, l, EncryptRsa);
    printf("The seed is:\n%s\n\n\n\n\n", seed);
    for (int i = 0; i < l; ++i)
        printf("0x%02x ", *(outseed+i));
    printf("\n");
    //send encrypted seed
    sendSeed(outseed,l,sock);
    unsigned char data_after_encrypt[16];
    unsigned char data_after_decrypt[16];
    unsigned char aesSeed[16];
    unsigned char expansionkey[15*16];
    strncpy((char*)aesSeed,(const char*)seed,16);
    ScheduleKey(aesSeed, expansionkey, 4, 10);

    //receive data
    printf("Waiting For File...\n");
    memset(data_after_encrypt,0,sizeof(data_after_encrypt));
    recvFile(data_after_encrypt,data_after_decrypt,expansionkey,sock);
    
    close(sock);
    return 0;
}
