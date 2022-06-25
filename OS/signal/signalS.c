#include <stdio.h>//기본 함수
#include <stdlib.h>//기본 함수
#include <signal.h> //시그널 함수 사용
#include <unistd.h>//write등 함수를 위해 사용
#include<sys/types.h>//named pipe를 사용하기위해 사용
#include<sys/stat.h>//named pipe를 사용하위해 사용
#include<fcntl.h>//파이프 관련 함수
#include<string.h>//string 관련 함수
#define FIFO_FILENAME "./textfifo"//named pipe 이름 선언

void do_write(char ch[]) //파이프 작성 함수
{
	int fd;//파이프 주소
	char buf[128];//버퍼
	strncpy(buf,ch,sizeof(buf));//버퍼에 전달받은 매개변수 카피
	unlink(FIFO_FILENAME);//연결되어 있을 수 있는 파이프를 언링크
	mkfifo(FIFO_FILENAME,0644);//파이프 생성
	fd=open(FIFO_FILENAME,O_WRONLY);//파피르를 쓰기모드로 오픈
	write(fd,buf,strlen(buf));//buf에 들어있는 글씨는 파이프에 작성
	close(fd);//파이프 연결 해제
}
void func(int sig)//시그널 핸들링
{
	char out[128];//글자 버퍼 생성
	if(sig==SIGINT) //SIGINT가 들어왔을때
	{
		strcpy(out,"SIGINT");//out버퍼에 "SIGINT"를 대입
		do_write(out);//do_write함수를 매개변수 out를 이용하여 사용
	}
	if(sig==SIGTSTP)//SIGTSTP가 들어왓을때
	{
		strcpy(out,"SIGTSTP");//out버퍼에 "SIGTSTP"를 대입
		do_write(out);//매개변수를 이요하며 do_write사용
	}
}
int main(int argc,char *argv[])
{
	signal(SIGINT,func);//SIGINT 시그널 핸들링
	signal(SIGTSTP,func);//SIGTSTP 시그널 핸들링
	while(1);//프로그램이 종료되지 않게 하기위한 무한반복
}


