#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Parm{
	int** Mat; 
	int** Mat2;
	int** res; 
	int deb, deb1,N;
}Parm;

int ** CreationMatriceA(int N)
{
	int i,j;
	int ** MatA;
	MatA = (int**)malloc(sizeof(int*)*N);
	 
	for (i=0; i<N;i++){
		MatA[i] = (int*)malloc(sizeof(int)*N);
	  for(j=0;j<N;j++){
	  	MatA[i][j] = 1;
	  }	
		
	}
return MatA;
}

int ** CreationMatriceB(int N)
{
	int i,j;
	int ** MatB;
	MatB = (int**)malloc(sizeof(int*)*N);
	 
	for (i=0; i<N;i++){
		MatB[i] = (int*)malloc(sizeof(int)*N);
	  for(j=0;j<N;j++){
	  	MatB[i][j] = i*N + j;
	  }	
		
}
return MatB;
}

void * creationParm(int **mat1,int **mat2, int **res, int debut1,int debut2, int N)
{
	Parm *p = (Parm*)malloc(sizeof(Parm));
	p->Mat = mat1; p->Mat2 = mat2;  
	p->res = res; p->deb=debut1; p->deb1=debut2;
	p->N=N;
	return (void *)p;
}

void * calculeSommeMatrice(void *P)
{
	Parm *Pa = (Parm*) P;
	
	int debut = Pa->deb;
	int deb1 = Pa->deb1;
	int ** mat = Pa->Mat;  
	int ** mat2 = Pa->Mat2;
	int **resultat = Pa->res;
	int N = Pa->N;
	int i,j;
	for (i=debut;i<(debut+N/2);i++)
		for (j=deb1;(j<deb1+N/2);j++)
		{	
			resultat[i][j] = mat[i][j]+mat2[i][j];
		}
return P; 
}


int ** CreationMatriceC(int N)
{
	int i,j;
	int ** MatA;
	MatA = (int**)malloc(sizeof(int*)*N);
	 
	for (i=0; i<N;i++){
		MatA[i] = (int*)malloc(sizeof(int)*N);
		
	}
return MatA;
}

int Verif(int **Matrice, int N)
{
	int i,j;
	for (i=0; i<N;i++)
		  for(j=0;j<N;j++)
		  {
		  	if (Matrice[i][j] != i*N+j+1)
		  		return 0;
		  }
	return 1;
}

int main()
{
	int N = 1000;
	int **MatriceA = CreationMatriceA(N);
	int **MatriceB = CreationMatriceB(N);
	int **MatriceC = CreationMatriceC(N);


	pthread_t t1,t2,t3,t4;

	pthread_create(&t1,0,calculeSommeMatrice,creationParm(MatriceA,MatriceB,MatriceC,0,0,N));	
	pthread_create(&t2,0,calculeSommeMatrice,creationParm(MatriceA,MatriceB,MatriceC,0,N/2,N));
	pthread_create(&t3,0,calculeSommeMatrice,creationParm(MatriceA,MatriceB,MatriceC,N/2,0,N));
	pthread_create(&t4,0,calculeSommeMatrice,creationParm(MatriceA,MatriceB,MatriceC,N/2,N/2,N));
	
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);	

	if (Verif(MatriceC,N)==0)
		printf("Vrai");
		else printf("FAUX");
	printf("%d",MatriceC[0][0]);	
return 0;		
}


