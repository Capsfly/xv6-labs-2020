//
// Created by suichunyu on 1/29/23.
//
#include "common_kernel_head.h"
void i2a(int val,char *arr)
{

    int temp_val=val;
    if(val==0)
    {
        arr[0]='0';
        arr[1]='\0';

    }
    else
    {
        int cnt=0;

        while(temp_val)
        {
            cnt++;
            temp_val/=10;
        }

        arr[cnt]='\0';
        for(int i=cnt-1;i>=0;i--)
        {
            arr[i]=val%10+'0';
            val/=10;
        }

    }
}

void myStrCat(char* str1,char* str2,char *dest)
{
    int idx=0;
    for(int i=0;str1[i]!='\0';i++)
    {
        dest[idx++]=str1[i];
    }
    for(int i=0;str2[i]!='\0';i++)
    {
        dest[idx++]=str2[i];
    }
    dest[idx]='\0';
}

void print_prime(int val)
{
    printf("prime %d\n",val);
}



void get_file_name(char*path,char*name)
{
    char* ptr;
    char* end_of_path=path+ strlen(path);
    for(ptr=path+ strlen(path);ptr>=path&&*ptr!='/';ptr--);
    ptr++;
    memmove(name,ptr,end_of_path-ptr+1);
}