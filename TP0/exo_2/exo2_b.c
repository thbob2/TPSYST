#include <stdio.h>  
#include <sys/types.h> 
#include <unistd.h>  
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
int val;

printf("vi:1\n cat:2\n rm:3\n");
scanf("%d",&val);

switch (val){
case 1: execlp( "vi",argv[1],NULL );
case 2: execlp( "cat","cat",argv[1],NULL );
case 3: execlp("rm","rm", argv[1],NULL);
}

return 0;}
