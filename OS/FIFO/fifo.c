#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> //nkfifo
#include <sys/stat.h> //mkfifo
#include <fcntl.h> //RDOUNY,WRONRY

#define FIFO_FILENAME "./testfifo"

int do_reader(char ch)
{
	
	int fd;
	char buf[128];
//printf("읽기모드\n");
	fd=open(FIFO_FILENAME,O_RDONLY);

	read(fd,buf,sizeof(buf));
	printf("%c) %s\n",ch,buf);
	


}
int do_writer()
{
	
	int fd;
	char buf[128];
	char in[128];

	scanf("%s",in);
//	printf("입력완료\n");
	unlink(FIFO_FILENAME);
	mkfifo(FIFO_FILENAME,0644);
	fd=open(FIFO_FILENAME,O_WRONLY);

	
	strncpy(buf,in,sizeof(buf));
	write(fd,buf,strlen(buf));
//	printf("쓰기완료\n");

}

void set(char input)
{
	if(input=='A')
	{
		do_reader('B');
	}
	else if(input=='B')
	{
		do_writer('A');
	}
	else
	{
		exit(0);
	}
}

int main(int argc,char *argv[])
{
	


	char input;
	scanf("%c",&input);
	
	set(input);
	return 0;
}
