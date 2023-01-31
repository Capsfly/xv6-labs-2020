#include "common_kernel_head.h"
#include "/home/suichunyu/Desktop/xv6-labs-2020/kernel/fs.h"

char*
fmtname(char *path)
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

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  // Directory is a file containing a sequence of dirent structures.
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

    /* Get file attributes for the file, device, pipe, or socket
     that file descriptor FD is open on and put them in BUF.  */
  if(fstat(fd, &st) < 0)
  {// fd is an id which identifies the path
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type)
  {
  case T_FILE://file
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

      memmove(p, de.name, DIRSIZ);//move name
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

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}
