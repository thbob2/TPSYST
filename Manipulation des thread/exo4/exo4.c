#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

typedef enum Posi{PIERRE=0,FEUILLE=1,CISEAU=2}Posi;

typedef struct Parm
{
	int joueur;
	Posi* posi1;
	Posi* posi2;
	int* point1;
	int* point2;
	sem_t* sem1;
	sem_t* sem2;
	sem_t* sem3;
	sem_t* sem4;
}Parm;

void printfPosi(Posi p)
{
	if(p==PIERRE)
		printf("pierre");
	else if(p==FEUILLE)
		printf("feuille");
	else
		printf("ciseau");
}

void* conterPoint(void* parm)
{
	Parm* p=(Parm*) parm;
	sem_wait(p->sem1);
	sem_wait(p->sem2);
	printfPosi(*(p->posi1));
	printf("\t");
	printfPosi(*(p->posi2));
	printf("\n");
	switch(*(p->posi1))
	{
		case PIERRE :
			if(*(p->posi2)==PIERRE)
			{
				*(p->point2)=*(p->point2)+1;
				*(p->point1)=*(p->point1)+1;
			}
			else if(*(p->posi2)==FEUILLE)
				*(p->point2)=*(p->point2)+1;
			else
				*(p->point1)=*(p->point1)+1;
		break;
		case FEUILLE :
			if(*(p->posi2)==FEUILLE)
			{
				*(p->point2)=*(p->point2)+1;
				*(p->point1)=*(p->point1)+1;
			}
			else if(p->posi2==PIERRE)
				*(p->point1)=*(p->point1)+1;
			else
				*(p->point2)=*(p->point2)+1;
		break;
		case CISEAU :
			if(*(p->posi2)==CISEAU)
			{
				*(p->point2)=*(p->point2)+1;
				*(p->point1)=*(p->point1)+1;
			}
			else if(*(p->posi2)==FEUILLE)
				*(p->point1)=*(p->point1)+1;
			else
				*(p->point2)=*(p->point2)+1;
		break;
		default : break;
	}
	sem_post(p->sem3);
	sem_post(p->sem4);

	return parm;
}

void* lireVal(void* parm)
{
	static Posi posis[]={PIERRE,FEUILLE,CISEAU};
	Parm* p=(Parm*) parm;
	int joueur1=(p->joueur)==1;
    	int val=rand()%(3);
	if(joueur1)
	{
		sem_wait(p->sem3);
		*(p->posi1)=posis[val];
		sem_post(p->sem1);
	}
	else
	{
		sem_wait(p->sem4);
		*(p->posi2)=posis[val];
		sem_post(p->sem2);
	}
	return parm;
}

void* CreationParm(int* point1,int* point2,Posi* posi1,Posi* posi2,sem_t* sem1,sem_t* sem2,sem_t* sem3,sem_t* sem4,int joueur)
{
	Parm* res=(Parm*) malloc(sizeof(Parm));
	res->point1=point1;
	res->point2=point2;
	res->posi1=posi1;
	res->posi2=posi2;
	res->joueur=joueur;
	res->sem1=sem1;
	res->sem2=sem2;
	res->sem3=sem3;
	res->sem4=sem4;
	return (void*)res;
}

int main(int argc,char** argv)
{
	srand(time(0));
	const int n=16;
	int i=0;
	pthread_t t1,t2,t3;
	Posi posi1,posi2;
	int point1=0;
	int point2=0;
	sem_t sem1,sem2,sem3,sem4;
	sem_init(&sem1,0,0);
	sem_init(&sem2,0,0);
	sem_init(&sem3,0,1);
	sem_init(&sem4,0,1);
	for(i;i<n;i++)
	{
		pthread_create(&t1, 0, lireVal, CreationParm(&point1,&point2,&posi1,&posi2,&sem1,&sem2,&sem3,&sem4,1));
		pthread_create(&t2, 0, lireVal, CreationParm(&point1,&point2,&posi1,&posi2,&sem1,&sem2,&sem3,&sem4,2));
		pthread_create(&t3, 0, conterPoint, CreationParm(&point1,&point2,&posi1,&posi2,&sem1,&sem2,&sem3,&sem4,0));
	}
if(point1>point2)
	printf("\nLe Joueur 1  a gagné avec : %d\t contre Joueur 2 = %d\n\n",point1,point2);
else
	printf("\nLe Joueur 2  a gagné avec : %d\t contre Joueur 1 = %d\n\n",point2,point1);
	
	return 0;
}
