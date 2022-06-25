#include <stdio.h>//기본 함수
#include <stdlib.h>//기본 함수
#include <signal.h> //시그널 함수 사용
#include <unistd.h>//파이프 관련 함수
#include <sys/types.h>//파이프 관련 함수
#include <sys/stat.h>//파이프 관련 함수
#include<fcntl.h>//read 함수
#include<string.h>//string 함수
#define FIFO_FILENAME "./textfifo"//파이프 이름은 전역으로 선언

void do_reader()//read함수
{
	int fd;//파이프 주소를 저장하기 위한 변수 선언
	char buf[128];//파이프에서 읽은 변수를 저장하기 위한 버퍼 선언
	fd = open(FIFO_FILENAME,O_RDONLY);//파이프를 읽기모드로 오픈
	read(fd,buf,sizeof(buf));//fd주소의 파이프를 buf의 크기만큼buf로 읽음
	close(fd);//파이프 연결 해제
	printf("%s 시그널을 받았습니다.\n",buf);//buf에 있는 단어를 출력
	exit(0);//프로세스 종료
}

void func(int sig)//시그널 핸들링
{
	char input;//단어를 저장하기 위한 변수
	if(sig==SIGINT)//SIGINT 신호가 들어왔을때
	{
		printf("종료할까요?(Y/N)\n");//단어를 출력
		scanf("%c",&input);//사용자가 입력한 단어를 저장
		if(input =='Y')//사용자가 입력한 단어가 'Y'면
			exit(0);//프로세스 종료
	}
	if(sig==SIGTSTP)//SIGTSTP가 들어왔을때
	{
		printf("힌호 수신.\n");//단어 출력
		do_reader();//reader함수 실행
	}
}


int main(int agc,int agv[])
{
	signal(SIGINT,func);//SIGINT시그널 핸들링
	signal(SIGTSTP,func);//SIGTSTP시그널 핸들링
	while(1);//main함수 종료를 막기위한 무한반복

}
