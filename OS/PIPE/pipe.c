#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> //fork,pipe 등
#include<sys/types.h>//fork
#include<sys/wait.h> //wait
int main(int argc,char argv[])
{
	int pipe_fds[2]; //파이프라인생성
	pid_t pid; // fork를 저장하기 위한 자료형
	char buf[1024]; //글자를 저장할 버퍼

	memset(buf,0,sizeof(buf)); //buf 배열을 0으로 buf의 크기까지 초기화

	if(pipe(pipe_fds)){
		return -1; //파이프가 형성되지 않으면 종료
	}
	pid = fork(); //pid에 fork된 분기를 넣음
	if(pid == 0) //자식 프로세스인 경우
	{
		close(pipe_fds[1]); //write를 닫음 -> read만 가능
		read(pipe_fds[0],buf,sizeof(buf)); //파이프라인으로부터buf의 값을 읽음
		printf("Child Process : Received \"%s\" form Parent\n",buf);
		close(pipe_fds[0]); //파이프라인을 닫아서 종료
	}
	else if (pid >0) //부모 프로세스일때
	{
		close(pipe_fds[0]);//read를 닫음
		strncpy(buf,"1234",sizeof(buf)); //buf값에 1234을 넣음
		write(pipe_fds[1],buf,strlen(buf));//파피르라인으로 buf를 작성
		printf("Parent Process : Send \"%s\" to Chile..\n",buf);
		close(pipe_fds[1]);//파피프라인 닫음

		wait(NULL); //좀비프로세스 방지
	}

	return 0;
}

