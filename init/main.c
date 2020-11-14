#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t sem_1;
sem_t sem_2;
void *Program2(void *arg);
void *Program3(void *arg);

int main()
{
	srand(time(NULL));
	//incializamos los semaforos
	sem_init(&sem_1,0,1);
	sem_init(&sem_2,0,0);
	//creamos los procesos
	pthread_t thread_1,thread_2;
	int number = rand()%10;
	
	if(0 != pthread_create(&thread_1,NULL,Program2,&number))
		printf("Failed of thread creation\n");

	pthread_create(&thread_2,NULL,Program3,NULL);
	
	printf("-----Start_Program------\n");

	pthread_join(thread_1,NULL);
	pthread_join(thread_2,NULL);
	
	printf("-----End_Program-----\n");

	return 0;
}

void *Program2(void *arg)
{
	int Number = *((int*)arg);
	sem_wait(&sem_1);
	if(Number%2==0)
	{
		printf("Even Number: %d\n",Number);
	}
	sem_post(&sem_2);
	
	printf("Thread_1 End\n");
}

void *Program3(void *arg)
{
	int Number = *((int*)arg);
	sem_wait(&sem_2);
	if(Number%2 ==1)
	{
		printf("Odd Number: %d\n",Number);
	}
	sem_post(&sem_1);

	printf("Thread_2 End\n");
}



