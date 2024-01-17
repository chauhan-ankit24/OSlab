// 1 - Windows subsystem for linux
// 2 - Virtual box
// 3 - Dual boot

// nano file_name.c // create or open existing
// gcc file_name.c // execute
// ./a.out // run
// man write // man 2 read // man lseek - to open manual

// ctrl + x - back
// ctrl + l - clear

// File descriptor  // 0 stdin - keyboard
// 1 stdout - on screen
// 2 stderr - screen
// rest user defined ( can be known by open call)

// ************************* WRITE system call *************************
#include <unistd.h>
#include <stdio.h>
int main()
{
    int n;
    n = write(1, "Hare Krishna\n", 13);
    printf("value returned is %d\n", n);
}

// ************************* READ system call *************************
#include <unistd.h>
int main()
{
    int n;
    char b[30];
    n = read(0, b, 30);
    write(1, b, n);
}

// ************************* OPEN system call *************************
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
    int n, fd, fd1;
    char buf[50];

    // fd = open("test.txt", O_RDONLY);
    // n = read(fd, buf, 10);
    // fd1 = open("target", O_CREAT | O_WRONLY, 0642);

    n = read(0, buf, 20);
    fd1 = open("target", O_WRONLY);

    write(fd1, buf, n);
}

// *************************  lseek system call *************************
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int n, f, f1;
    char buff[10];
    f = open("seeking", O_RDWR); // 1234567890abcdefghijx1x2x3x4x5

    read(f, buff, 10); // 1234567890 // from pointer at 1
    write(1, buff, 10);
    read(f, buff, 10); // abcdef // from pointer at a
    write(1, buff, 10);

    read(f, buff, 10); // 1234567890
    write(1, buff, 10);
    lseek(f, 10, SEEK_CUR); // re-positioning the pointer
    read(f, buff, 10);      // abcdefghij
    write(1, buff, 10);

    f1 = lseek(f, 10, SEEK_SET); // return final setted position of pointer
    printf("Pointer is at %d position\n", f1);
    read(f, buff, 10);
    write(1, buff, 10); // abcdefghij

    f1 = lseek(f, -11, SEEK_END);
    read(f, buff, 10);
    write(1, buff, 10); // x1x2x3x4x5
}
// ************************* dup & dup2 system call *************************
//  will be assigned to the lowest file descriter
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main()
{
    int fd, fd1;
    fd = open("dup", O_RDONLY);
    printf("OLD file descriptor %d\n", fd);

    // fd1 = dup(fd);
    // printf("NEW file descr. %d\n", fd1);

    fd1 = dup2(fd, 7);
    printf("New personalized file desc %d\n", fd1);
}

// ************************* fork() system call *************************
// to create a child process
// can return 3 values
// error q<0, q==0 child, q>0 parent

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t q;
    q = fork(); // if success, from this line we have two process , child and parent
    if (q < 0)
        printf("error");
    else if (q == 0)
    {   // child process
        // write code here for child
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getppid());
    }
    else
    { // q>0; parent process
        printf("Parent having pid %d\n", getpid());
        printf("My Child's pid is %d \n", p);
    }
}
// before fork
// Parent having pid 888
// My Child's pid is 889
// child having pid 889
// My Parent's pid is 339
// above order can vary as we have two process and any one can get CPU first

// *************************  WAIT system call *************************
// to control the order of above sequence
// parent will wait for child to terminate


// *************************  system call *************************
// *************************  system call *************************
// *************************  system call *************************
// *************************  system call *************************
// *************************  system call *************************
