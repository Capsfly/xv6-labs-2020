//
// Created by suichunyu on 1/30/23.
//

#include "common_kernel_head.h"
#include "my_function.c"
#define EOP (-1)
void seive(int fa2node[2])
{
    int must_is_prime;
    read(fa2node[0], &must_is_prime, sizeof (must_is_prime));

    print_prime(must_is_prime);

    int node2son[2];
    pipe(node2son);

    int id=fork();
    if(id<0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(id==0)//son process
    {
        seive(node2son);
        exit(0);
    }
    else//parent process
    {
        int now_val;
        while(read(fa2node[0],&now_val, sizeof(now_val))!=EOP)
        {

            if(now_val%must_is_prime!=0)
            {
                write(node2son[1],&now_val, sizeof(now_val));
            }
        }
        exit(0);
    }
}

int main()
{





}
























