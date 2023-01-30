//
// Created by suichunyu on 1/29/23.
//
#include "common_kernel_head.h"
#include "my_function.c"
#define NULL 0
int main()
{

    int fields1[2];//father process sends data to son
    pipe(fields1);

//    int fields2[2];//son process sends data to father
//    pipe(fields2);

    if(fork()>0)
    {
        char send_data[]="received ping";

        printf("write %d bytes\n", write(fields1[1], send_data, sizeof(send_data)));

        wait(NULL);

        char read_buf[50];
        i2a(getpid(),read_buf);

        strcpy(read_buf+ strlen(read_buf),":");

//        read(fields2[0], read_buf + strlen(read_buf), sizeof(read_buf) - sizeof(char) * strlen(read_buf));

        fprintf(2,read_buf);
    }
    else//pid==0
    {
        char test[150];

        int cnt=read(fields1[0], test,14);
        printf("%d\n",cnt);
        printf("%s\n",test);

        char read_buf[150];
        i2a(getpid(),read_buf);

        strcpy(read_buf+ strlen(read_buf),":");

        strcpy(read_buf+ strlen(read_buf),test);
        //read(fields1[0], read_buf + strlen(read_buf), sizeof(read_buf) - sizeof(char) * strlen(read_buf));

        printf("%s\n", read_buf);

//        char send_data[50]="received pong";

//        write(fields2[1], send_data, sizeof(send_data));

    }
    exit(0);

}

