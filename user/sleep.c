#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int second;

    if(argc <= 1){
        fprintf(2, "usage: sleep [second ...]\n");
        exit(1);
    }

    argv = argv + 1;
    second = atoi(*argv);
    sleep(second);

    exit(0);
}
 