
#include "kernel/types.h"
#include "user.h"


int main(int argc, char* argv[]){
   if(argc != 1){
      printf("Pingpong doesn't need arguments");
   }
   int fd[2]={0};
   int fd2[2]={0};
   pipe(fd);
   pipe(fd2);
   int status;
   int pid_t = fork();
   if (pid_t==0){
      char* buf[32]={0};
      close(fd[1]);
      close(fd2[0]);
      int giv2 = write(fd2[1],"pong",32);
      int rec = read(fd[0],buf,32);
      if(rec < 0){
         printf("child read error!");
         exit(-1);
      }
      if(giv2 < 0){
         printf("child write error!");
	      exit(-1);
      }
      printf("%d: received %s\n",pid_t,buf);
      close(fd[0]); 
      exit(0);
   }else{
      char* buf[32]={0};
      close(fd[0]);
      close(fd2[1]);
      sleep(5);
      int giv = write(fd[1],"ping",32);
      int rec2 = read(fd2[0],buf,32);
      if(giv < 0){
         printf("write error!");
	      exit(-1);
      }
      if( rec2 < 0){
         printf("father read error!");
	      exit(-1);
      }
      wait(&status);
      printf("%d: received %s\n",pid_t,buf);
      close(fd[1]);
   }
   exit(0);
}

