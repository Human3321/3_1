#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp = fopen("1.txt","a");
	char name[100]={0};
	char age[10]={0};
	char check;


	while(1)
	{
		printf("이름: ");
		scanf(" %[^\n]s",name);
		printf("나이: ");
		scanf(" %s",age);
		printf("계속 출력 하기셌습니까(Y/N) ");
		printf("1  %c\n",check);
		scanf(" %c",&check);
		printf("2  %c\n",check);
		fprintf(fp,"%s/%s",name,age);
		if(check=='N')
		{
			printf("종료");
			break;
		}
	}
	fclose(fp);

	return 0;
}
