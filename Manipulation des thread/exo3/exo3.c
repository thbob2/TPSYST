#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int compteur[3];

int A[16][16];
int B[16][16];
int C[16][16];

/////////
void * fonc_thread(void *k)
{
	printf("thread numero %ld : mon tid est %ld \n",(long) k, pthread_self());
	for(;;) compteur[(long) k]++;
}
/////////

////////////

void * add_matrice_haut_droite(void *t)
{
	int i,j;
	for(i=0; i<8;i++)
	{ 	for(j=8; j<16;j++)
		{ C[i][j]=A[i][j]+B[i][j];
		 }
		}
}
void * add_matrice_haut_gauche(void *t)
{
	int i,j;
	for(i=0; i<8;i++)
	{ 	for(j=0; j<8;j++)
		{ C[i][j]=A[i][j]+B[i][j];
		 }
		}
}
void * add_matrice_bas_droite(void *t)
{
	int i,j;
	for(i=8; i<16;i++)
	{ 	for(j=8; j<16;j++)
		{ C[i][j]=A[i][j]+B[i][j];
		 }
		}
}
void * add_matrice_bas_gauche(void *t)
{
	int i,j;
	for(i=8; i<16;i++)
	{ 	for(j=0; j<8;j++)
		{ C[i][j]=A[i][j]+B[i][j];
		 }
		}
}


main()
{
	int i,j;
	for( i=0; i<16;i++)
	{ 	for( j=0; j<16;j++)
		{ A[i][j]=1;
		 }
		}

	for(i=0; i<16;i++)
		{ 	for(j=0; j<16;j++)
			{ B[i][j]=i*16+j;
			 }
			}

pthread_t pth_id[4];
long  num=1; 
	pthread_create(&pth_id[1], 0, add_matrice_haut_droite, NULL);
printf("Main : thread numero %ld cree : id = %ld \n",num, pth_id[num]);
pthread_join(pth_id[1],NULL);

num=2;
	pthread_create(&pth_id[2], 0, add_matrice_haut_gauche,NULL);
printf("Main : thread numero %ld cree : id = %ld \n",num, pth_id[num]);
pthread_join(pth_id[2],NULL);

num=4;
	pthread_create(&pth_id[4], 0, add_matrice_bas_gauche, NULL);
printf("Main : thread numero %ld cree : id = %ld \n",num, pth_id[num]);
pthread_join(pth_id[4],NULL);

num=3;
	pthread_create(&pth_id[3], 0, add_matrice_bas_droite, NULL);
printf("Main : thread numero %ld cree : id = %ld \n",num, pth_id[num]);
pthread_join(pth_id[3],NULL);

	usleep(1600);
	 printf(" affichage des resultats \n");
	
		for( i=0; i<16;i++)
		{ 	for( j=0; j<16;j++)
			{ printf("%d 	",C[i][j]);
			 }
		printf("\n");
			}

	exit(0);
}
