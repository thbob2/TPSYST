#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (){ 
	int i=0,status, tab[3], total[3];
	pid_t pid, ppid, npid;
	pid=(pid_t) getpid();
	for (i=0;i<=2;i++) {
		npid=( pid_t )fork();
		 if (npid == -1) {printf("erreur");}
		 else { if (npid==0){if (i==0) exit(5); 	 //fils1 
		 		if (i==1) exit(10);//fils2
				if (i==2)exit(3);//fils3
		 }else { 	
		 			tab[i]=npid;
					waitpid(tab[i],&status,0);
					total[i]=WEXITSTATUS(status);
					printf("Exit code: %d\n", WEXITSTATUS(status));
				}
			}
		}
printf("total=%d\n",total[2]*total[1]+total[0]);
return 0;
}