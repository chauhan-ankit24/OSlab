// 1 - Windows subsystem for linux
// 2 - Virtual box
// 3 - Dual boot

// nano file_name.c
// gcc file_name.c
// ./a.out



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

// *************************  system call *************************

// *************************  system call *************************

// *************************  system call *************************

// *************************  system call *************************
