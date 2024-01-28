// 1 - Windows subsystem for linux
// 2 - Virtual box
// 3 - Dual boot

// nano file_name.c // create or open existing
// gcc file_name.c // execute
// ./a.out // run
// man write // man 2 read // man lseek - to open manual

// ctrl + x - back
// ctrl + l - clear
// ps - which process are runnning in system
//

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
// pid - process id
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
    { // child process
        // write code here for child
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getppid());
    }
    else
    { // q>0; parent process
        printf("Parent having pid %d\n", getpid());
        printf("My Child's pid is %d \n", q); // The value of q will be the child process ID in the parent process and 0 in the child process.
    }
    printf("common\n");
}
// before fork
// Parent having pid 888
// My Child's pid is 889
// child having pid 889
// My Parent's pid is 339
// common
// common // two times as common for both process
// above order can vary as we have two process and any one can get CPU first

// *************************  WAIT system call *************************
// to control the order of above sequence
// parent will wait for child to terminate not child for parent, child will wait for his own child

// to wait child for parent, use sleep(can be used for both ), will not wait for parent to end but will wait for specified time

//  wait,  waitpid,  waitid  -  wait  for process to change state
//   A state change is considered to be: the child terminated;
//    the child was stopped by a signal; or the child was re‐
//    sumed  by a signal.

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t q;
    q = fork(); // if success, from this line we have two process , child and parent
    if (q < 0)
        printf("error");
    else if (q == 0)
    { // child process
        // write code here for child
        sleep(3);
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getpid());
    }
    else
    { // q>0; parent process
        printf("Parent having pid %d\n", getpid());
        wait(NULL); // above line will execute but below one will wait
        printf("My Child's pid is %d \n", q);
    }
    printf("common\n");
}

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t q;
    q = fork();
    if (q < 0)
        printf("error");
    else if (q == 0)
    {
        sleep(3);
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getpid());
    }
    else
    {
        // w=wait(NULL);
        w1 = wait(&wstatus);                          // process id of child that has changed the state
        printf("Status is %d\n", WIFEXITED(wstatus)); // return true if state change was by normal termination of child
        // printf("Status is %d\n",w1);
        printf("My child's id is %d\n", w1);
        printf("I am parent having id %d\n", getpid());
        printf("Parent having pid %d\n", getpid());
        printf("My Child's pid is %d \n", q);
    }
    printf("common\n");
}

// When we want parent to wait for perticular child process of some pid
int main()
{
    pid_t p, q;
    printf("before fork\n");
    p = fork();
    if (p == 0) // child1
    {
        printf("I am first child having Pid %d\n", getpid());
        printf("My parent's Pid is %d\n", getppid());
    }
    else
    { // parent
        q = fork();
        if (q == 0) // child2
        {
            printf("I am second child having PID %d\n", getpid());
            printf("Second child's parent PID is %d\n", getppid());
        }
        else
        {
            // wait(NULL);
            waitpid(p, NULL, 0); // will wait for p child process
            printf("I am parent having id %d\n", getpid());
            printf("My First child's PID is %d\n", p);
            printf("My Second child's PID is %d\n", q);
        }
    }

    // *************************  Create an ORPHAN process *************************

    if (p == 0)
    {
        sleep(5); // child goes to sleep and in the mean time parent terminates
        printf("I am child having PID %d\n", getpid());
        printf("My parent PID is %d\n", getppid());
    }
    else
    {
        printf("I am parent having PID %d\n", getpid());
        printf("My child PID is %d\n", p);
    }
}
// use ps command to see process running

// *************************  Create an Zonbie Process *************************
int main()
{
    pid_t q;
    q = fork();
    if (q == 0)
    {
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getppid());
    }
    else
    {
        sleep(3);
        printf("Parent having pid %d\n", getpid());
        printf("My Child's pid is %d \n", q);
    }
}
// OUTPUT
// run 'ps' command
// we will still get the entry of child process even though it is finished ; infrotn of it we will get --> " <defunct> "

// HOW to avoid zombie process
// use wait(NULL)
// will not get <defunct>

int main()
{
    pid_t q;
    q = fork();
    if (q == 0)
    {
        printf("child having pid %d\n", getpid());
        printf("My Parent's pid is %d\n", getppid());
    }
    else
    {
        wait(NULL); // till child goes to termination state
        sleep(3);
        printf("Parent having pid %d\n", getpid());
        printf("My Child's pid is %d \n", q);
    }
}
// *************************  execl() system call *************************
// To replace current process image with a new one

int main()
{
    printf("Before\n");
    execl("/bin/ls", "ls", "-1", NULL);
    printf("After\n");
}
// usage :
// with fork() a child process is created which will do the dame work as the parent(same code) but with use f execl we can change the code of child entirely.
int main()
{
    pid_t q;
    q = fork();
    if (q == 0)
    { // child
        execl("/bin/ls", "ls", "-1", NULL);
    }
    else
    { // parent
        wait(NULL);
        printf("I am parent having id %d\n", getpid());
    }
}
// *************************  create threads *************************
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg);
int i, n, j;

int main()
{
    pthread_t a_thread;                                      // thread declaration
    pthread_create(&a_thread, NULL, thread _function, NULL); // thread is created
    thread_join(a_thread, NULL);                             // process waits for thread to finish . without this both for loop will get merged
    printf("Inside Main Program\n");
    for (j = 20; j < 25; j++)
    {
        printf("%d \n", j);
        sleep(1);
    }
}
void *thread_function(void *arg)
{ // the work to be done by the thread is defined in this function
    printf("Inside Thread\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d \n", i);
        sleep(1);
    }
}

// output
// Inside Thread
// 0
// 1
// 2
// 3
// 4
// Inside Main Program
// 20
// 21
// 22
// 23
// 24

// *************************  Passing value to threads *************************

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg);
int num[2] = {3, 5};

int main()
{
    thread_t a_thread; // thread declaration
    void *result;
    thread_create(&a_thread, NULL, thread_function, (void *)num); // thread is created
    thread_join(a_thread, &result);                               // result stores the value returned by the thread
    printf("Inside Main process\n");
    printf("Thread returned: %s\n", (char *)result);
}
void *thread_function(void *arg)
{
    // the work to be done by the thread is defined in this functio
    printf("Inside Thread\n");
    int *x = arg;
    int sum = x[0] + x[1];
    printf("Sum is %d\n", sum);
    thread_exit("sum calculated"); // value returned
}
// *************************  Race Condition *************************
// thread1 will increase
// thread2 will decrease
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *fun1();
void *fun2();
int shared = 1; // shared variable

int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value of shared is %d\n", shared); // prints the last updated value of shared variable
}
void *fun1()
{
    int x;
    x = shared; // thread one reads value of shared variable
    printf("Thread1 reads the value of shared variable as %d\n", x);
    x++; // thread one increments its value
    printf("Local updation by Thread1: %d\n", x);
    sleep(1);   // thread one is preempted by thread 2
    shared = x; // thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);
}
void *fun2()
{
    int y;
    y = shared; // thread two reads value of shared variable
    printf("Thread2 reads the value as %d\n", y);
    y--; // thread two increments its value
    printf("Local updation by Thread2: %d\n", y);
    sleep(1);   // thread two is preempted by thread 1
    shared = y; // thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);
}
// OUTPUT
// Thread1 reads the value of shared variable as 1
// Local updation by Thread1: 2 // thread1 sleeps
// Thread2 reads the value as 1
// Local updation by Thread2: 0
// Value of shared variable updated by Thread2 is: 0
// Value of shared variable updated by Threadi is: 2
// Final value of shared is 2 // if u interchange the function final value will be 0

// ************************* Proces Syncronization : SEMAPHORES *************************

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
void *fun1();
void *fun2();
int shared = 1; // shared variable
sem_t s;        // semaphore variable
int main()
{
    sem_init(&s, 0, 1); // initialize semaphore variable - 1st argument is address of variable, 2nd is number of processes sharing semaphore, 3rd argument is the initial value of semaphore variable
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value of shared is %d\n", shared); // prints the last updated value of shared variable
}
void *fun1()
{
    int x;
    sem_wait(&s); // executes wait operation on s
    x = shared;   // thread1 reads value of shared variable
    printf("Thread1 reads the value as %d\n", x);
    x++; // thread1 increments its value
    printf("Local updation by Thread1: %d\n", x);
    sleep(1);   // thread1 is preempted by thread 2
    shared = x; // thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);
    sem_post(&s);
}
void *fun2()
{
    int y;
    sem_wait(&s);
    y = shared; // thread2 reads value of shared variable
    printf("Thread2 reads the value as %d\n", y);
    y--; // thread2 increments its value
    printf("Local updation by Thread2: %d\n", y);
    sleep(1);   // thread2 is preempted by thread 1
    shared = y; // thread2 updates the value of shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);
    sem_post(&s);
}
// OUTPUT
//  Thread1 reads the value as 1
//  Local updation by Thread1: 2
//  Value of shared variable updated by Thread1 is: 2
//  Thread2 reads the value as 2
//  Local updation by Thread2: 1
//  Value of shared variable updated by Thread2 is: 1
//  Final value of shared is 1

// ************************* Proces Syncronization : Mutex locks *************************

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void *fun1();
void *fun2();
int shared = 1;    // shared variable
pthread_mutex_t l; // mutex lock
int main()
{
    pthread_mutex_init(&l, NULL); // initializing mutex locks
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value of shared is %d\n", shared); // prints the last updated value of shared variable
}
void *fun1()
{
    int x;
    printf("Thread1 trying to acquire lock\n");
    pthread_mutex_lock(&l); // thread one acquires the lock. Now thread 2 will not be able to acquire the lock //until it is unlocked by thread 1
    printf("Thread1 acquired lock\n");
    x = shared; // thread one reads value of shared variable
    printf("Thread1 reads the value of shared variable as %d\n", x);
    x++; // thread one increments its value
    printf("Local updation by Thread1: %d\n", x);
    sleep(1);   // thread one is preempted by thread 2
    shared = x; // thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);
    pthread_mutex_unlock(&l);
    printf("Thread1 released the lock\n");
}
void *fun2()
{
    int y;
    printf("Thread2 trying to acquire lock\n");
    pthread_mutex_lock(&l);
    printf("Thread2 acquired lock\n");
    y = shared; // thread two reads value of shared variable
    printf("Thread2 reads the value as %d\n", y);
    y--; // thread two increments its value
    printf("Local updation by Thread2: %d\n", y);
    sleep(1);   // thread two is preempted by thread 1
    shared = y; // thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);
    pthread_mutex_unlock(&l);
    printf("Thread2 released the lock\n");
}
// OUTPUT
// Threadi trying to acquire lock
// Thread1 acquired lock
// Thread2 trying to acquire lock
// Thread1 reads the value of shared variable as 1
// Local updation by Thread1: 2
// Value of shared variable updated by Threadi is: 2
// Thread1 released the lock
// Thread2 acquired lock
// Thread2 reads the value as 2
// Local updation by Thread2: 1
// Value of shared variable updated by Thread2 is: 1
// Thread2 released the lock
// Final value of shared is 1

// ************************* InterProcess Communication : popen/pclose *************************
// popen used to send / recieve from a process
// popen opens a pipe stream i.e, unidirectional
// 1st process will be the mentioned and second will be the mentioned

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{
    FILE *rd;
    char buffer[50];
    sprintf(buffer, "name first");
    rd = popen("wc -c", "w");                         // wc -c -> is the process which counts the number of characters passed. 2nd parameter is "w" which means pipe is opened in writing mode
    fwrite(buffer, sizeof(char), strlen(buffer), rd); // to write the data into the pipe
    pclose(rd);
}

// ************************* InterProcess Communication : pipe() *************************
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int fd[2], n;
    char buffer[100];
    pid_t p;
    pipe(fd); // creates a unidirectional pipe with two end fd[0] and fd[1]
    p = fork();
    if (p > 0) // parent
    {
        printf("Parent Passing value to child\n");
        write(fd[1], "hello\n", 6); // fd[1] is the write end of the pipe
        wait();
    }
    else // child
    {
        printf("Child printing received value\n");
        n = read(fd[0], buffer, 100); // fd[0] is the read end of the pipe
        write(1, buffer, n);
    }
}
