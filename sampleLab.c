// 1 - Windows subsystem for linux
// 2 - Virtual box
// 3 - Dual boot

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

// *************************  system call *************************

// *************************  system call *************************

// *************************  system call *************************

// *************************  system call *************************

// *************************  system call *************************
