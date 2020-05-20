#include "receiver.h"
#include "aes.h"

int sendSeed(unsigned char *seed,int s_len,int sock){
    char* data=(char*)seed;
    int len=s_len;
    int rc;
     do{
        rc=write(sock, data, len);
        if(rc<0){
            printf("errno while sending seed is %d\n",errno);
            exit(0);
        }else{
            data+=rc;
            len-=rc;
        }
    }while(len>0);
    return len;
}

int recvEncryptedData(unsigned char *dae,int d_len,int sock){
    int rc;
    int len=d_len;
    do{
        rc=read(sock, dae, len);
        if(rc<0){
            printf("errno while receiving encrypted data is %d\n",errno);
            exit(0);
        }else{
            dae+=rc;
            len-=rc;
        }
    }while(len>0);
    return 0;

}

int recvPKeyAndLen(unsigned char *b_f, int32_t *pk_len,int sock){
    int left1=sizeof(*pk_len);
    int left2=0;
    char *data=(char*)pk_len;
    int rc1;
    int rc2;
    do{
        rc1=read(sock, data, left1);
        if(rc1<0){
            printf("errno while receiving public key length is %d\n",errno);
            exit(0);
        }else{
            data+=rc1;
            left1-=rc1;
        }
    }while(left1>0);


    left2=ntohl(*pk_len);
    do{
        rc2=read(sock, b_f, left2);
        if(rc2<0){
            printf("errno while receiving public key is %d\n",errno);
            exit(0);
        }else{
            b_f+=rc2;
            left2-=rc2;
        }
    }while(left2>0);
    return 0;
}

int genSeed(unsigned char* ranstr){
    int i,flag;
    srand(time(NULL));
    for(i = 0; i < SEED_LEN-1; i ++)
    {
		flag = rand()%3;
		switch(flag)
		{
		case 0:
			*(ranstr+i) = rand()%26 + 'a';
			break;
		case 1:
			*(ranstr+i) = rand()%26 + 'A';
			break;
		case 2:
			*(ranstr+i) = rand()%10 + '0';
			break;
		}
    }
    return i;
}

int recvFile(unsigned char *data_after_encrypt,unsigned char *data_after_decrypt,unsigned char *expansionkey,int sock){
    unsigned long fsize=0;
    char fs[8];
    char p_fs[16];
    recvEncryptedData((unsigned char*)p_fs,sizeof(p_fs),sock);
    strncpy(fs,(const char*)p_fs,8);
    fsize=*((unsigned long*)fs);
    //~ printf("encrypt File size:%lu\n",fsize);
    Contrary_AesEncrypt((unsigned char*)p_fs,expansionkey, 10);
    strncpy(fs,(const char*)p_fs,8);
    fsize=*((unsigned long*)fs);
    printf("File size:%lu\n",fsize);
    unsigned long times=((unsigned long)(fsize/16))+1;
    char fn[256];
    memset(fn,0,sizeof(fn));
    recvEncryptedData((unsigned char*)fn,sizeof(fn),sock);
    //~ printf("encrypt File name:%s\n",fn);
    Contrary_256_AesEncrypt((unsigned char*)fn, expansionkey, 10);
    printf("File name:%s\n",fn);
    FILE *fp;
    if((fp=fopen((const char*)fn,"wb"))==NULL){
        printf("File error!\nEnding the program!\n");
        exit(0);
    }
    printf("Writing file...\n");
    for(int i=0;i<times;i++){
        recvEncryptedData(data_after_decrypt,16,sock);
        Contrary_AesEncrypt(data_after_decrypt, expansionkey, 10);
        if(i!=times-1){
            fwrite(data_after_decrypt,16,1,fp);
        }else{
            fwrite(data_after_decrypt,fsize%16,1,fp);
        }
    }
    fclose(fp);
    printf("Completes!\n");
}
