#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct human{
	char ID[256];
	char name[256];
	char gender[10];
	int age;
};


struct test{
	char pp[10][256];
};
struct US{
	struct human h;
	int HP,MP,coin;
};


void encode(char input[],char output[])
{
//	struct US user;
	struct test t;
	int count=0;
	strcat(output,".bin");
	FILE* fp=fopen(input,"r");
	FILE* wp=fopen(output,"wb");

	char buf[256];
	int len;
	while(fgets(buf,256,fp))
	{
		len=strlen(buf);
		strcpy(buf,t.pp[count++]);
//		fwrite(buf,sizeof(char),len,wp);
	}
	fwrite(&t,sizeof(t),1,wp);
	fclose(fp);
	fclose(wp);

//	wp=fopen(output,"rb");
//	fread(
}



int main(int argc,char* argv[])
{
	if(argc==3)
		encode(argv[1],argv[2]);
	else if(argc==2)
	{
	FILE* tp=fopen("asd.bin","wb");
	char bf[256]={'a','b','c'};
	fwrite(bf,sizeof(char),3,tp);
	fclose(tp);
	}
	else
		printf("./encoder.out \"입력파일명\" \"출력파일명\"\n");
	
	return 0;
}

