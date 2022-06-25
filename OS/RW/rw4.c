#include <stdio.h>// 기본 함수 사용
#include <sys/time.h> // gettimeofdaty 사용
#include<unistd.h> // POSIX API제공
#include<stdlib.h> // thread
#include<pthread.h> //thread 사용



int rw_mutex =1;
int mutex =1;

void wait(int s)
{
	while(s<=0)
	{

	}
	s--;
}

void signal(int s)
{
	s++;
}

int acc=0;
int readcount=0;
int now_access=0;


void* write_th(void *arg)
{
	printf("write 시작\n");
	int i=0;
	while(1)
	{	i++;
		wait(rw_mutex);
		if(i>=100)
		{
			acc++;
			i=0;
		}
		if(acc>=10)
			acc=0;
		signal(rw_mutex);
		if(readcount>=1000)
			break;
	}
	printf("write 끝\n");
}

void* read_th(void *arg)
{
	int i=0;
	printf("read 시작\n");
	while(1)
	{
		wait(mutex);
		if(acc>8)
			readcount++;
		while(i<100000)
		{
			i++;
		}
		i=0;
		signal(mutex);
		if(readcount>=1000)
			break;
	}
	printf("read끝\n");
}


int main()
{
	struct timeval time1,time2;
	double time;
	int i;
	gettimeofday(&time1,NULL);
	pthread_t th[20];

	for(i=0;i<10;i++)
		pthread_create(&th[i],NULL,write_th,NULL);
	for(i=10;i<20;i++)
		pthread_create(&th[i],NULL,read_th,NULL);

/*
	pthread_create(&th[0],NULL,write_th,NULL);
	pthread_create(&th[1],NULL,read_th,NULL);
	pthread_create(&th[2],NULL,read_th,NULL);
	pthread_create(&th[3],NULL,read_th,NULL);
	pthread_create(&th[4],NULL,read_th,NULL);
	pthread_create(&th[5],NULL,read_th,NULL);
	pthread_create(&th[6],NULL,read_th,NULL);
	pthread_create(&th[7],NULL,read_th,NULL);	
	pthread_create(&th[8],NULL,read_th,NULL);
	pthread_create(&th[9],NULL,read_th,NULL);
	pthread_create(&th[10],NULL,read_th,NULL);
	pthread_create(&th[11],NULL,read_th,NULL);
	pthread_create(&th[12],NULL,read_th,NULL);
	pthread_create(&th[13],NULL,read_th,NULL);
	pthread_create(&th[14],NULL,read_th,NULL);
	pthread_create(&th[15],NULL,read_th,NULL);
	pthread_create(&th[16],NULL,read_th,NULL);
	pthread_create(&th[17],NULL,read_th,NULL);
	pthread_create(&th[18],NULL,read_th,NULL);
	pthread_create(&th[19],NULL,read_th,NULL);
*/
pthread_join(th[0],NULL);
	pthread_join(th[1],NULL);
	pthread_join(th[2],NULL);

	gettimeofday(&time2,NULL);
	time=(time2.tv_sec-time1.tv_sec)+((time2.tv_usec-time1.tv_usec)/1000000.);

	printf("%f\n",time);
	return 0;
}
