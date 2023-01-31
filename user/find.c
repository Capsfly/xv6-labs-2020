//
// Created by suichunyu on 1/30/23.
//

#include "common_kernel_head.h"
#include "my_function.c"
#include "/home/suichunyu/Desktop/xv6-labs-2020/kernel/fs.h"

char* fmtname(char *path)
{
    static char buf[DIRSIZ+1];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if(strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
    return buf;
}

void find(char *path,char* target_name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    // Directory is a file containing a sequence of dirent structures.
    struct stat st;

    if((fd = open(path, 0)) < 0)
    {
        printf("ls: cannot open %s\n", path);
        exit(1);
    }

    /* Get file attributes for the file, device, pipe, or socket
     that file descriptor FD is open on and put them in BUF.  */
    if(fstat(fd, &st) < 0)
    {// fd is an id which identifies the path
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    char obj_name[100];
    switch(st.type)
    {
        case T_FILE://file
            get_file_name(path, obj_name);
            if(strcmp(obj_name,target_name)==0)
            {

            }
            printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);

            break;

        case T_DIR:// Directory
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
            {// handle the exception
                printf("ls: path too long\n");
                break;
            }
            strcpy(buf, path);//put path in buf(char[])
            p = buf+strlen(buf);
            *p++ = '/';

            while(read(fd, &de, sizeof(de)) == sizeof(de))
            {
                if(de.inum == 0)
                    continue;

                memmove(p, de.name, DIRSIZ);//move target_name
                p[DIRSIZ] = 0;//set end of char[]
                //buf stores the absolute path
                if(stat(buf, &st) < 0)
                {
                    //stat:Get file attributes for the file, device, pipe, or socket
                    //that file descriptor FD is open on and put them in BUF.
                    printf("ls: cannot stat %s\n", buf);
                    continue;
                }
                printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
            }
            break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{

    exit(0);
}




