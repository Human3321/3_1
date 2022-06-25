#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
int main()
{
	printf("Hello\n"); //첫 Hello
	printf("Hello\n");//두번째 Hello
	fork(); // fork()로 분기생성
	printf("Hello\n");//부모 프롯스스 1번, 자식 프로세스 1번 3,5번째
	printf("Hello\n");//부모 프로세스 1번, 자식 프로세스 1번 4,6번째
	wait(NULL); //프로세스를 멈추는 코드 없으면 프로그램이 계속 실행
return 0;
}
