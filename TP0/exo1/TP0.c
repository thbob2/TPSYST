#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{ int statut,fils;
pid_t pid, ppid,npid;
pid = getpid();
printf ( "programme main PID : %d\n", pid);
// création processus fils
npid =fork();
if(npid == -1)
{
	printf("erreur");
}
else 
	{
		if (npid == 0)  
		{	sleep(5);
			//le programme fils
			pid = getpid();
			ppid = getppid();
			printf ("Le PID du fils  : %d\n", pid);
			printf ("Le PID du parent est : %d\n", ppid);
		}
	 	else
	 	{
 			sleep(2);
			//on est dans le pere
			pid = getpid();
			ppid = getppid();
			printf ("Le PID courant : %d\n", pid);
			printf ("Le PID pere est : %d\n", ppid);
			//fils=wait(&statut);
			printf("my sons watch %d is over \n",fils);
		}
	}
return 0;
}