#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>

int a,b,c,x1,x2,delta;
pid_t  pid1,pid2,pid3;
 
void handler_son1(int sign){
	printf(" I've found the first solution \n");
}


void handler_son2(int sign){
	printf(" I've found the second solution \n");
}
void main()
{	
	signal(SIGUSR1, handler_son1);
	signal(SIGUSR2, handler_son2);
	while(1){
		puts("{a,b,c}=/= 0");
		puts(" give me the value of a ");
		scanf("%d",&a);
		puts(" give me the value of b ");
		scanf("%d",&b);
		puts(" give me the value of c ");
		scanf("%d",&c);
		delta = pow(b,2)-4*b*c;
		printf(" delta = %d",delta);
		if(delta>=0){ // sénario 1 
			pid1 = fork();
			// si on est ddans le 1er fils
			if(pid1==0){
				x1 = (-b-sqrt(delta))/2/a;
				printf("(the first solution x1=%d)\n",x1);
				kill(getppid(),SIGUSR1);
				exit(0);
			}else{
					pid2 = fork();
					// si on est ddans le 2em fils
					if(pid2==0){
					x1 = (-b+sqrt(delta))/2/a;
					printf("(the second solution x2=%d)\n",x2);
					kill(getppid(),SIGUSR2);
					exit(0);
					}
			while(wait(NULL)!=-1);		
			}}
			else{ // sénario 2 
				pid3=fork();
				if(pid3==0){execlp("./stop","stop",NULL);}
				else wait(0);
			}}}
