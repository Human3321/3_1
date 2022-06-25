#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv)
{
	FILE *fp = fopen("file2.txt","w");
	char a[100];
	if(fp==NULL)
	{
		fprintf(stderr,"error\n");
		exit(1);
	}
	scanf("%s",a);
	fputs(a,fp);

	fclose(fp);

	return 0;


}
