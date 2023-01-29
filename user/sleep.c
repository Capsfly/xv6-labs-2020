#include "common_kernel_head.h"


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "Usage: sleep <seconds>\n");
        exit(1);
    }
    else
    {
        sleep(0);
        exit(0);
    }

}