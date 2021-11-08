#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void 
readAndSend(int *recv_pipe) 
{
    int n, p;
    int send_pipe[2];

    pipe(send_pipe);
    close(recv_pipe[1]);

    if(read(recv_pipe[0], &p, 4) <= 0) {
        exit(0);
    }
    printf("prime %d\n", p);

    if(fork()) {
        close(send_pipe[0]);
        while (read(recv_pipe[0], &n, 4) > 0) {
            if (n % p != 0) {
                write(send_pipe[1], &n, 4);
            }
        }        
        close(send_pipe[1]);
        wait((int *) 0);
    }else {
        readAndSend(send_pipe);
        exit(0);
    }
}

int 
main()
{
    int recv_pipe[2];
    pipe(recv_pipe);

    int i;    
    if (fork() == 0) {
        close(recv_pipe[0]);
        for(i = 2; i <= 35; i++) {
            write(recv_pipe[1], &i, 4);
        }
        close(recv_pipe[1]);
        exit(0);
    }

    readAndSend(recv_pipe);
    wait((int *) 0);
    exit(0);
}

