#include <stdio.h>// 기본 함수 사용
#include <sys/time.h> // gettimeofdaty 사용
#include<unistd.h> // POSIX API제공
#include<stdlib.h> // thread
#include<pthread.h> //thread 사용

double multi_j=0; //멀티스레드 접근을 위한 전역 변수

void* funtion(void *arg){ //멀티스렏를 돌리기 위한 함수 선언
	int i=0;//반복문을 위한 함수
	while(1)//무한 반복
	{
		i++;//i값 증가
		if(i==150000)//i가 150000이 되면
		{
			i=0; //i를 0으로 초기화
			multi_j++;//전역변수인 multi_j를 1 증가
		}
		if(multi_j==1000)//multi_j가 1000이 되면
			break;//반복문 종료 -> 스레드 종료
	}
}

struct timeval do_single_thread(){ //싱글 스레드
	struct timeval time1,time2,time3; //timeval구조체 변수 3개 선언
	gettimeofday(&time1,NULL);//함수 시작할때 time1에 시간 삽입
	double i=0,j=0;//변수 선언
	double t;//변수 선언
	while(1)//무한 바복
	{
		i++;//i증가
		if(i==150000)//i가 150000일때
		{	j++;//j증가
			i=0;//i는 0으로 초기화
		}
		if(j==1000)//j가 1000이될때
			break;//반복문 탈출
	}
	gettimeofday(&time2,NULL);//반복문이 끝나고 time2에 시간 삽입
	time3.tv_sec=time2.tv_sec-time1.tv_sec;
	//time3에 time2에서 time1을 뺀 초단위 시간 삽입
	time3.tv_usec=time2.tv_usec-time1.tv_usec;
	//time3에 itme2에서 time1을 뺀 MS단위 시간 삽입
	t=time3.tv_sec+(time3.tv_usec/1000000.);//초단위와 마이크로초단위 합체뒤에 나누기를 한 이유는 MS단위를 맞추기 위해
	printf("single_thread:\n");
	printf("결과: %f, 소요시간: %f초\n",j,t);
	//j의 값과 동작한 시간 출력
	return time3;
	//return 값으로 함수가 동작한 시간의 값을 넣음


}
struct timeval do_multi_thread(){ //멀티스레드
	struct timeval time1,time2,time3; //timeval구조체 변수 3개 선언
	gettimeofday(&time1,NULL);//함수 시작할때 time1에 시간 삽입
	double j=0,t; //변수 선언
	pthread_t th[4];//pthread 4개 선언
	pthread_create(&th[0],NULL,funtion,NULL);//1번 thread 생성
	pthread_create(&th[1],NULL,funtion,NULL);//2번 thread 생성
	pthread_create(&th[2],NULL,funtion,NULL);//3번 thread 생성
	pthread_create(&th[3],NULL,funtion,NULL);//4번 thread 생성
	pthread_join(th[0],NULL);//1번 스레드가 끝날때까지 main함수 종료 대기
	pthread_join(th[1],NULL);//2번 스레드가 끈날때까지 main함수 종료 대기
	pthread_join(th[2],NULL);//3번 스레드가 끈날때까지 main함수 종료 대기
	pthread_join(th[3],NULL);//4번 스레드가 끝날때까지 main함수 종료 대기

	gettimeofday(&time2,NULL);//반복문을 나오고 나서 사간을 time2에 삽입
	time3.tv_sec=time2.tv_sec-time1.tv_sec;
	//time3.tv_sec에 반복문 동작동안의 시간을 삽입
	time3.tv_usec=time2.tv_usec-time1.tv_usec;
	//time3.tv_usec에 반복문 동작동안의 시간을 삽입
	t=time3.tv_sec+(time3.tv_usec/1000000.);
	//t에 초단위와 MS초 단위의 값 합체
	printf("multi_thread:\n");
	printf("결과: %f, 소요시간: %f초\n",multi_j,t);
	//multi_j의 값과 경과한 시간 출력
	return time3;
	//return값으로 동작한 시간을 timeval 구조체로 반환
}


void print_diff(struct timeval single,struct timeval multi){ 
//시간 차이를 비교하는 함수
	double t1,t2,diff;//실수형으로 변수 선언
	t1=single.tv_sec+(single.tv_usec/1000000.);
	//t1에는 싱글스레드의 시간 삽입
	t2=multi.tv_sec+(multi.tv_usec/1000000.);
	//t2에는 멀티스레드의 시간 삽입
	diff=t1/t2;
	//싱글스레드와 멀티스레드의 동작 시간을 비교


	printf("시간 비고:\n");
	printf("multi thread가 single thread 대비 %f배 빠르게 수행 되었음.\n",diff);

}


int main(int argc, char* argv[])
{
	struct timeval single_thread_processing_time = do_single_thread();
	struct timeval multi_thread_processing_time = do_multi_thread();

	print_diff(single_thread_processing_time,multi_thread_processing_time);

	return 0;
}
