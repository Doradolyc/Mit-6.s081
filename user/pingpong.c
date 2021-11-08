#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int p1[2], p2[2];
    char str[1024];

    pipe(p1);
    pipe(p2);

    if(fork() == 0) {
        close(p1[1]);
        read(p1[0], str, 1024);
        close(p1[0]);

        if(strcmp(str, "ping\n") == 0) {
            printf("%d: received ping\n", getpid());
            close(p2[0]);
            write(p2[1], "pong\n", 6);
            close(p2[1]);
        }
    } else {
        //0 receive
        //1 send
        close(p1[0]);
        write(p1[1], "ping\n", 6);
        close(p1[1]);

        close(p2[1]);
        read(p2[0], str, 1024);
        close(p2[0]);
        if(strcmp(str, "pong\n") == 0) {
            printf("%d: received pong\n", getpid());
        }
    }
    exit(0);
}