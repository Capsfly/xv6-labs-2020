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

    int fields2[2];//son process sends data to father
    pipe(fields2);

    int id=fork();
    if(id<0)
    {
        printf("error\n");
        exit(1);
    }
    else if(id>0)
    {
        char send_data[]="received ping";

        write(fields1[1], send_data, 1);

        wait(NULL);

        char read_buf[50];
        i2a(getpid(),read_buf);

        strcpy(read_buf+ strlen(read_buf),":");

        read(fields2[0], read_buf + strlen(read_buf), sizeof(read_buf) - sizeof(char) * strlen(read_buf));

        printf("%d: received pong\n",getpid());
//        fprintf(2,read_buf); maybe some bugs here
    }
    else//pid==0
    {
        char read_buf[150];
        i2a(getpid(),read_buf);
        strcpy(read_buf+ strlen(read_buf),":");

        read(fields1[0], read_buf + strlen(read_buf), 1);

        printf("%d: received ping\n", getpid());

        char send_data[]="received pong";

        write(fields2[1], send_data, sizeof(send_data));

    }
    exit(0);

}