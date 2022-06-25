#include <stdio.h>//기본 함수
#include <stdlib.h>//기본 함수
#include <signal.h> //시그널 함수 사용


void func(int sig)
{
	char input;
	if(sig==SIGINT){
		printf("종료할까요?(Y/N)\n");
		scanf("%c",&input);
		if(input =='Y')
			exit(0);
	}
	if(sig==SIGTSTP)
	{
		printf("CTRL+Z가 입력되었씁니다.\n");
	}
}


int main(int agc,int agv [])
{
	signal(SIGINT,func);
	signal(SIGTSTP,func);
	while(1);

}
