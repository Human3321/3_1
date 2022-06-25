#include<stdio.hd>
#include<stdlib.h>

struct player{
	char ID[256];
	short age;
	int HP;
	double x,y;
	char frend[255][256];
}P;

void player_add()

void player_check()

int main(int argc,char* argv[])
{
	int input;
	while(1)
	{
		printf("1. 플레이어 정보 기록\n");
		printf("2. 풀래아오 종보 확인\n");
		printf("3. 종료\n");
		scanf("%d",&input);
		if(input==1)
			player_add();
		else if(input==2)
			player_check();
		else if(input==3)
			break;
	}
	return 0;
}

