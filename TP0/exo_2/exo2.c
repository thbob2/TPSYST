#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <sys/wait.h>
#include <stdlib.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
int i;
if (argc==1){
 execlp( "ls", "~", NULL );}
else
{execlp( "ls", "ls",argv[1], NULL );}

return 0;}