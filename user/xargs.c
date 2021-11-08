#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

char *
substr(const char *str, int begin, int end, char* res)
{
    for(int i = 0; i < (end - begin); i++) {
        res[i] = str[begin + i];
    }
    return res;
}


char **
spilt(char str[], char ** argvs)
{  
    int before = 0, index = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == ' ') {
            char res[i - before + 1];
            memset(res, 0, i - before + 1);
            argvs[index++] = substr(str, before, i + 1, res);
            before = i + 1;
        }
    }

    return argvs;
}

int
main(int argc, char *argv[])
{
    int index = 0, i;
    const int MAXN = 1 << 7;
    char buf[MAXN], cur[MAXN];

    if (argc < 2) {
        fprintf(2, "usage: do sth | xargs do sth\n");
        exit(1);
    }

    char* exe = argv[1];
    for (i = 0; i < argc - 1; i++) {
        argv[i] = argv[i + 1];
    }


    read(0, buf, MAXN);

    for(i = 0; i < strlen(buf); i++) {
        if (buf[i] == '\n' || i == strlen(buf) - 1) {

            if(fork() == 0) {
                argv[argc - 1] = cur;
                exec(exe, argv);
            }
            index = 0;
            memset(cur, 0, sizeof(cur));
            wait((int *)0);
        } else {
            cur[index++] = buf[i];
        }   
    }

    exit(0);
}