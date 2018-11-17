#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>

int main(){
	int a, b, c , pid1 , pid2, pid3, status,val;
	float delta, x1, x2;
	while(1)
	{
		printf("a = ");
		scanf("%d",&a);	
		printf("b = ");		
		scanf("%d",&b);	
		printf("c = ");		
		scanf("%d",&c);
		delta=((b*b)-(4*a*c));
		if(delta >= 0)
		{	printf("delta = %f .\n",delta);
			pid1 = fork();
		    if(pid1==0)
			{
				x1=(-b-sqrt(delta))/(2*a); 		
				printf("j ai trouvé la 1ere solution (%f)\n",x1);
				printf("x1 = %f \n",x1);
				return 1;
			}
			pid2 = fork();
			if(pid2==0)				
			{			
				x2=(-b+sqrt(delta))/(2*a);
				printf("x2 = %f \n",x2);
			 	printf("j ai trouvé la 2eme solution (%f)\n",x2);
			 	return 2;
			}
			while(wait(NULL)!=-1);	
			//wait(&status);
			waitpid(pid1,&status,0);
			waitpid(pid2,&status,0);
			val=WEXITSTATUS(status);

			
		}
		/*else
		{ 
			pid3=fork();
			{
				printf("le processus de resolution des equations est termine...\n");
				exit(1);
			}
		}	*/
	}
}