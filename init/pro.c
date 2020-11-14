#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

void *Program2(void *arg);
void *Program3(void *arg);

int Number;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc,char *argv[])
{
        int t;
	srand(time(NULL));
	t = atoi(argv[1]);
	while(t--){
	  pthread_t thread_1,thread_2;
	  //int number;
	  Number = rand()%100;
	
          pthread_create(&thread_1,NULL,Program2,NULL);//&number
	  pthread_create(&thread_2,NULL,Program3,NULL);//&number
	
	  pthread_join(thread_1,NULL);
	  pthread_join(thread_2,NULL);
	}
	return 0;
}

void *Program2(void *arg)
{
	//int Number = *((int*)arg);

	printf("--------Even Nnumber Origin: %d\n",Number);
	
	if(Number%2==0)
	{
		pthread_mutex_lock(&mutex);
		Number+=2;
		pthread_mutex_unlock(&mutex);
		
		printf("Even Nnumber: %d\n",Number);
	}
	//printf("Thread_1 end\n");
}


void *Program3(void *arg)
{
	//int Number = *((int*)arg);

	printf("---------Odd Nnumber Origin: %d\n",Number);
	
	if(Number%2==1)
	{ 
		pthread_mutex_lock(&mutex);
		Number+=2;
		pthread_mutex_unlock(&mutex);
		
		printf("Odd Number: %i\n",Number);
	}
	//printf("Thread_2 end\n");
}
