#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp1 = fopen("text3.txt","w");
	FILE *fp2 = fopen("file2.txt","r");
	char c;
	int check;
	if(fp1==NULL)
		fprintf(stderr,"오류\n");	
	if(fp2==NULL)
		fprintf(stderr,"오류\n");
	while((check=fscanf(fp2,"%c",&c))!=EOF)
	{
		fprintf(fp1,"%c",c);
		
	}
	fclose(fp1);
	fclose(fp2);

	return 0;

}
