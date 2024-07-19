#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>

void error(int n){
    switch (n)
    {
    case 1:
        printf("Error: File Read Error\n");
        exit(1);
    case 2:
        printf("Error: Not match data size\n");
        exit(2);
    case 3:
        printf("Error: Need more arguments\n");
        exit(3);
    default:
        printf("Unknown Error\n");
        exit(-1);
    }
}

void readFile(char* path, uint32_t *data){
    FILE *fp = fopen(path,"r");
    if(fp == NULL){
        error(1);
    }
    fseek(fp, 0, SEEK_END); 
    long int size = ftell(fp);
    if (size != 4){
        error(2);
    }
    fseek(fp,0,SEEK_SET);
    fread(data,32,1,fp);
    *data = ntohl(*data);
    fclose(fp);
    fp=NULL;
}


int main(int argc, char* argv[]){
    uint32_t data[argc];
    if(argc == 1){
        error(3);
    }
    data[0] = 0;
    for(int i=1; i != argc; ++i){
        readFile(argv[i],&data[i]);
        printf("%u(0x%x) ",data[i] ,data[i]);
        if(i+1 != argc){
            printf("+ ");
        }
        data[0] += data[i];
    }
    printf("= %u(0x%x)\n",data[0],data[0]);
}