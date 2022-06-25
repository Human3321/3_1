#include<stdio.h>

int main(int argc,char* agrv)
{
	FILE *fp=fopen("asd.txt","w");
	char a[100];
	int i;
	for(i=0;i<3;i++)
	{
	scanf("%[^\n]s",a);
	fprintf(fp,"%s \n",a);
	printf("qqq\n");
	}
	fgets(fp);
	if(fp ==NULL)
		printf("error");
	else
		printf("파일열기 성공\n");
	fclose(fp);
	return 0;
}
