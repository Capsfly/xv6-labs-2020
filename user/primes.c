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
    close(fa2node[1]);
    if(must_is_prime==EOP)
    {
        exit(0);
    }
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
        close(node2son[0]);
        int now_val;
        while(1)
        {
            read(fa2node[0],&now_val, sizeof(now_val));
            if(now_val==EOP)
            {
                break;
            }
            if(now_val%must_is_prime!=0)
            {
                write(node2son[1],&now_val, sizeof(now_val));
            }
        }
        close(fa2node[0]);
        now_val=EOP;
        write(node2son[1],&now_val, sizeof(now_val));
        close(node2son[1]);
        wait(NULL);
        exit(0);
    }
}

int main()
{
    int input_pipes[2];
    pipe(input_pipes);

    for(int i=2;i<=35;i++)
    {
        write(input_pipes[1],&i, sizeof(i));
    }

    int eop=EOP;
    write(input_pipes[1],&eop, sizeof(eop));
    close(input_pipes[1]);
    seive(input_pipes);
    wait(NULL);
    close(input_pipes[0]);

    exit(0);
}