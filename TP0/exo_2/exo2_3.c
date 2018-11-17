
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>

 
 int main(int argc, char *argv[])
 {
     char *const parmList[] = {"somme","NULL"};
   

	printf("EXercice 2 - 3\n"); 
	execv("./sum",parmList);
	exit(EXIT_FAILURE);
 }