#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signal) {
    if (signal == SIGINT) {
        printf("Yeah!\n");
    } else if (signal == SIGHUP) {
        printf("Ouch!\n");
    }

}

int main(int argc, char* argv[])
{
    signal(SIGINT, &handler);

    signal(SIGHUP, &handler);


    /* declare i (integer) and n (number) */
    int i, n;
    
    /* upper limit input */
    sscanf(argv[1], "%d", &n); /* argv[1] is the number i pass on to program */

    /* for loop to check if i is under n, then add 2 to i if true */
    for(i=0; i<n; i++) // for loop, where i increments by 1 if it is lesser than n
    {
        printf("%d\n", i*2); // prints out i then doubles it by 2
        sleep(5);
    }

    /* can't put for loop before the scan because it would run loop then ask for the number
        only because i did it the uninitialized way
        and i'm being forced to not hardcode it
        this will not anger the compiler ...
        i think scanf will initialize them as the code runs 
        i am in pain */

    return 0;

}



