#include "/home/suichunyu/Desktop/xv6-labs-2020/kernel/types.h"
#include "/home/suichunyu/Desktop/xv6-labs-2020/kernel/stat.h"
#include "/home/suichunyu/Desktop/xv6-labs-2020/user/user.h"


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "Usage: sleep <seconds>\n");
        exit(1);
    }
    int time = atoi(argv[1]);
    sleep(time);

    exit(0);
}