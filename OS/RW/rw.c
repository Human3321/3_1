#include <stdio.h>// 기본 함수 사용
#include <sys/time.h> // gettimeofdaty 사용
#include<unistd.h> // POSIX API제공
#include<stdlib.h> // thread
#include<pthread.h> //thread 사용

pthread_mutex_t rw_mutex;
pthread_mutex_t mutex;

int acc=0;
int readcount=0;
int now_access=0;


void* write_th(void *arg)
{
	printf("write 시작\n");
	int i=0;
	while(1)
	{
		i++;	
		pthread_mutex_lock(&rw_mutex);
		if(i==1000&&acc==0)
		{
			acc=1;
			i=0;
		}
		if(i==1000&&acc==1)
		{
			acc=0;
			i=0;
		}
		pthread_mutex_unlock(&rw_mutex);
		if(readcount==100000)
			break;
	}
	printf("write 끝\n");
}

void* read_th(void *arg)
{
	printf("read 시작\n");
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(readcount==100000)
			break;
		now_access++;
		if(now_access==1)
			pthread_mutex_lock(&rw_mutex);
		pthread_mutex_unlock(&mutex);
		if(acc==1)
			readcount++;
		pthread_mutex_lock(&mutex);
		now_access--;
		if(now_access==0)
			pthread_mutex_unlock(&rw_mutex);
		pthread_mutex_unlock(&mutex);

	}
	printf("read끝\n");
}


int main()
{
	pthread_t th[3];

	pthread_mutex_init(&rw_mutex,NULL);
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&th[0],NULL,write_th,NULL);
	pthread_create(&th[1],NULL,read_th,NULL);
	pthread_create(&th[2],NULL,read_th,NULL);

	pthread_join(th[0],NULL);
	pthread_join(th[0],NULL);
	pthread_join(th[0],NULL);

	return 0;
}
