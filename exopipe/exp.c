#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int main(int argc, char const *argv[])
{
	int tube[2];
	pid_t pid,f1,f2,f3,f4;
	int r_max;
	//int p[4];
	/*
	for(int i=0;i<4;i++){
		p[i]=fork();
		if(p[i] == 0){
			r[i] = (rand()%900);
			printf("processuce pid:%d, noeud :%d val=%d \n",getpid(),i,r[i]);
			exit(0);
		}
	*/
		f1=fork();
		if(f1 == 0){
			int r1 = (rand()%900);
			r_max=r1;
			//char[100] str;
			printf("processuce pid:%d, noeud :%d val=%d \n",getpid(),0,r1);
			int tube0[2];
			pipe(tube0);
			close (tube0[0]);
			//itoa(r1,str,0); // a verifier 
			write (tube0[1],&r_max,sizeof(r_max));
			exit(0);
		}
		f2=fork();

		if(f2 == 0){
			int r;
			int r2 = (rand()%900);
			//char[100] str;
			printf("processuce pid:%d, noeud :%d val=%d \n",getpid(),1,r2);
			close(tube0[1 ]);
			read(tube0[0],&r_max,sizeof(r_max));
			int tube1[2];
			pipe(tube1);
			//r = atoi(str);
			if (r2>r_max){
				r_max=r2;				
				close(tube1[0]);
				//sprintf(str,"%d",r2);
				//itoa(r2,str,0);
				write(tube1[1],&r_max,sizeof(r_max));

			}else {
				/*close(tube1[0]);
				//itoa(r,str,0);
				sprintf(str,"%d",r);
				write(tube1[1],str,sizeof(str));*/
				close(tube1[0]);
				//sprintf(str,"%d",r2);
				//itoa(r2,str,0);
				write(tube1[1],&r_max,sizeof(r_max));
			} 
			exit(0);
		}


		f3=fork();
		if(f3 == 0){
			int r;
			int r3 = (rand()%900);
			//char[100] str;
			printf("processuce pid:%d, noeud :%d val=%d \n",getpid(),2,r3);
			close(tube1[1]);
			read(tube1[0],&r_max,sizeof(r_max));
			int tube2[2];
			pipe(tube2);
			//r = atoi(str);
			if (r3>r_max){
				r_max=r3;
				close(tube2[0]);
				//itoa(r3,str,0);
				//sprintf(str,"%d",r3);
				write(tube2[1],&r_max,sizeof(r_max));

			}else {
				close(tube2[0]);
				//itoa(r,str,0);
				//sprintf(str,"%d",r);
				write(tube2[1],&r_max,sizeof(r_max));

			} 
			exit(0);
		}

		f4=fork();

		if(f4== 0){
			int r4 = (rand()%900);
			//char[100] str;
			printf("processuce pid:%d, noeud :%d val=%d \n",getpid(),3,r4);
			close(tube2[1]);
			read(tube2[0],&r_max,sizeof(r_max));
			int tube3[2];
			pipe(tube3);
			//r = atoi(str);
			if (r4>r_max){
				r_max=r4;
				close(tube3[0]);
				//itoa(r3,str,0);
				//sprintf(str,"%d",r3);
				write(tube3[1],&r_max,sizeof(r_max));

			}else {
				close(tube3[0]);
				//sprintf(str,"%d",r);
				//itoa(r,str,0);
				write(tube3[1],&r_max,sizeof(r_max));

			} 
			exit(0);
		}	

	

	
	/* code */
	return 0;
}