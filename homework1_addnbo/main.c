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
    fp=0;
}


int main(void){
    uint32_t data[2];
    uint32_t tmp[2];
    readFile("thousand.bin",&data[0]);
    readFile("five-hundred.bin",&data[1]);
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",data[0],data[0],data[1],data[1],data[0]+data[1],data[0]+data[1]);
}