//
// Created by suichunyu on 1/29/23.
//
#include "common_kernel_head.h"
#include "user.h"
#define NULL 0
int main()
{
    int pid=fork();
    int fields[2];
    pipe(fields);

    if(pid<0)
    {
        fprintf(2,"error\n");
        exit(1);
    }
    else if(pid>0)
    {
        const char *text="ping";
        int a= strlen(text);
        write(fields[1],text,strlen(text));
        wait(NULL);
        char buf[50];
        read(fields[0],buf,sizeof(buf));
        char* container= malloc(20);

        fprintf()
    }
    else
    {

    }




}


















