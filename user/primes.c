#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[]){
    if(argc != 1){
       printf("Primes doesn't need arguments!");
       exit(-1);
    }
    int fd[2]={0};
    int status;
    pipe(fd);
    if(fork() == 0){
      while(1){
       int num = 0;
       int num1 = 0;
       int flag = 0;
       int fd2[2]={0};
       pipe(fd2);
       close(fd[1]);
       read(fd[0],&num1,sizeof(num));
       if(num1 == 36){
	    exit(0);
       }else{
          printf("prime %d\n",num1);
       }
       while(1){
	      read(fd[0],&num,sizeof(num));
         if(num % num1 != 0){
           if(num == 36){close(fd[0]);close(fd2[0]);close(fd2[1]);exit(0);}
	        flag =1;
	        break;
	      }
       }
      if(flag){
	    if(fork()==0){
	      close(fd[1]);
	      close(fd[0]);
	      fd[1] = dup(fd2[1]);
	      fd[0] = dup(fd2[0]);
	      close(fd2[1]);
	      close(fd2[0]);
	      continue;
	    }
	    else{
         close(fd2[0]);
         write(fd2[1],&num,sizeof(num));
         while(1){
	         read(fd[0],&num,sizeof(num));
	         if(num == 36){
		         write(fd2[1],&num,sizeof(num));
		         close(fd2[1]);
		         break;
		      }
	         else if(num % num1 != 0){
	            write(fd2[1],&num,sizeof(num));
	         }
	      }
	   }
     }
      break;
      }
    }
    else{
       close(fd[0]);
       for(int i=2;i<=36;i++){
          write(fd[1],&i,sizeof(i));
       }
       close(fd[1]);	
    }
    wait(&status);
    exit(0);
}
