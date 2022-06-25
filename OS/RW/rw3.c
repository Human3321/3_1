#include <stdio.h>// 기본 함수 사용
#include <sys/time.h> // gettimeofdaty 사용
#include<unistd.h> // POSIX API제공
#include<stdlib.h> // thread
#include<pthread.h> //thread 사용


pthread_mutex_t mutex; //뮤텍스 선언

//int mutex=1;//뮤텍스 선언
//세마코어를 뮤텍스로 동작

void wait(int s) //세마포어 wait선언
{
	while(s<=0) //s가 0보다 작을때 대기
	{

	}
	s--; //s감소
}

void signal(int s) //세마포어 signal
{
	s++; //s증가
}

int c=0;
int acc=0; //접근 제어 변수
int readcount=0; //read스레드들이 접근한 수를 카운트
int now_access=0; //현재 read하는 스레드의 개수


void* write_th(void *arg) //wrtie 스레드
{
	printf("write 시작\n"); //스레드 시작을 출력
	int i=0; //일정 시간동안 증가하는 함수
	while(1)
	{	 //i를 증가시킴
		//wait(mutex); //rw변수로 lock
		pthread_mutex_lock(&mutex); //뮤텍스 lock -> 다른 스레드(read도) 접근이 불가
		c++;
		if(c>=100) //i가 100에 도달하면
		{
			acc++; //접근 변수 증가
			c=0; //i값 초기화
		}
		if(acc>=10) //접근변수가 10이상이면
			acc=0; //접근변수 초기화
		//signal(mutex); //unlock
		pthread_mutex_unlock(&mutex); //뮤텍스 unlock -> 다른 스레드가 접근이 가능
		if(readcount>=1000) //스레드 종료 조건
			break;
	}
	printf("write 끝\n");
}

void* read_th(void *arg) //read 스레드
{
	int i=0;//반복문 변수
	printf("read 시작\n");
	while(1)
	{
		pthread_mutex_lock(&mutex); //뮤텍스 락(다른 스레드 접근 불가)
	//	wait(mutex);//read에서만 동작하는 lock
			//크리티컬 섹션 시작
		if(acc>8) //접근변수가 8이상일때
			readcount++; //read된 수를 카운트하기 위해 사용
			//readcount는 동시성 접근 제어가 안됨
		while(i<100000) //read구역에서의 반복
		{
			i++;
		}
		i=0;
		//크리티컬 섹션 종료
		//signal(mutex);//read에서 동작하는  umlick
		pthread_mutex_unlock(&mutex);//뮤텍스 언락
		if(readcount>=1000)//스레드 종료 조건
			break;
	}
	printf("read끝\n");
}


int main()
{
	pthread_mutex_init(&mutex,NULL); //뮤텍스 초기화
	struct timeval time1,time2; //시간을 측정하기 위한 timeval구조체
	double time;//시간 변수
	int i;//스레드에 입력하기 위한 변수
	gettimeofday(&time1,NULL);//현제 시간을 time1에 저장
	pthread_t th[20];//스레드 배열 선언

	for(i=0;i<5;i++)//write스레드 생성
		pthread_create(&th[i],NULL,write_th,NULL);
	for(i=5;i<20;i++)//read스레드 생성
		pthread_create(&th[i],NULL,read_th,NULL);
	for(i=0;i<20;i++)//스레드가 끝나면 메인함수 종료
		pthread_join(th[i],NULL);
	gettimeofday(&time2,NULL);//스레드가 동작하고 난 뒤 시간을 time2에 저장
	time=(time2.tv_sec-time1.tv_sec)+((time2.tv_usec-time1.tv_usec)/1000000.); //시간 계산

	printf("%f\n",time);
	return 0;
}
