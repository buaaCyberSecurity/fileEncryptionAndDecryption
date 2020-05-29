#include "string.h"
#include "SHA256.h"
char s[1000010];
uint h[10];

int main(int argc,char *argv[]){    
	unsigned char path[4097];
    FILE* fp;
    strcpy((char *)path,argv[1]);
    if((fp = fopen((const char*)path,"rb"))!=NULL){	 
        //printf("File opening...\n");
        fread(s, 1, 1000000, fp);
        fclose(fp);
        //printf("\nthe sender SHA256-hash value is:\n");
        SHA256(s, h);
        for (int i = 0; i < 8; ++i)
            printf("%08x", h[i]);
        printf("\n");
    }
    return 0;
}
