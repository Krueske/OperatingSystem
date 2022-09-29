#include "kernel/types.h"
#include "user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    int i;
    char *params1[MAXARG];
    char buf[32];
    int status;
    for(i=1; i<=argc-1; i++){
        params1[i-1] = argv[i];
    }
    params1[argc] = 0;
    while(1){
        gets(buf,sizeof(buf));
        for(i=0;i<=sizeof(buf);i++){
            if(buf[i]=='\n'){
                buf[i] = 0;
                break;
            }
        }
        params1[argc-1] = buf;
        params1[argc] = 0;
        if(fork()==0){
            exec(argv[1], params1);
            exit(0);
        }
        wait(&status);
    }
    exit(0);
}