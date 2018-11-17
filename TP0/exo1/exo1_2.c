#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{ int statut,fils;
pid_t pid, ppid,n1pid,n2pid;
pid = getpid();
printf ( "programme main PID : %d\n", pid);
// création processus fils
puts("JE VAIS CRÉÉ FILS  ");
n1pid =fork();
if(n1pid == -1)
{ 
	printf("erreur");
}
else 
	{
		if (n1pid == 0)  
		{	sleep(5);
			//le programme fils1
			pid = getpid();
			ppid = getppid();
			printf ("fils1: %d  de :%d dit bonjour \n",pid, ppid);
			sleep(5);
			printf ("fils1: %d  de :%d dit au revoir \n",pid, ppid);
		}
	 	else {	
	 			puts("JE VAIS CRÉEE FILS ");
	 			n2pid=fork();
	 			if(n2pid == -1)
					{printf("erreur");}
				else 
				{	if (n2pid == 0)  
					{	
						//le programme fils2
						pid = getpid();
						ppid = getppid();
						printf ("fils2: %d  de :%d dit bonjour \n",pid, ppid);
						sleep(5);
						printf ("fils2: %d  de :%d dit au revoir \n",pid, ppid);
					}
	 				else
				 	{	while(wait(NULL) != -1);
				 		sleep(2);
						//on est dans le pere
						pid = getpid();
						ppid = getppid();
						printf ("Le PID courant : %d\n", pid);
						printf ("Le PID pere est : %d\n", ppid);	
					}
				}
			}
	}
return 0;
}