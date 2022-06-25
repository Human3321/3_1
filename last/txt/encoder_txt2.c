#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void encode(char input[],char output[])
{
	strcat(output,".txt");
	FILE* fp=NULL;//fopen(input,"r");
	FILE* wp=fopen(output,"w");
	char buf[256];
	char bp[200][256];
	char* a;
	int count=0;
	int count2=0;
	int i;
	for(i=0;i<3;i++)
	{
	fp=fopen(input,"r");
	count=0;
	count2=0;
	while(fgets(buf,256,fp))
	{
		if(strchr(buf,'*')!=NULL)
		{
			count2++;
			fprintf(wp,"%c\n",'@');
			continue;
		}
		a=strstr(buf,": ");
		if(a==NULL&&count2<4)
		{
			count++;
			fprintf(wp,"%c\n",'*');
			printf("*\n");
			continue;
		}
		if(count==1)
		{
			fprintf(wp,"%s",buf);
		}
		else if(count2==4)
		{
			fprintf(wp,"%s",buf);
		}
		else
		{
			a=a+2;
		//	fprintf(wp,"%s",a);
			fprintf(wp,"%s",buf);	
		}
	}
	fclose(fp);
	}
//	fclose(fp);
	fclose(wp);
}

int main(int argc,char* argv[])
{
	if(argc==3)
		encode(argv[1],argv[2]);
	else
		printf("./encoder.out \"입력파일명\" \"출력파일명\"\n");
	
	return 0;
}

