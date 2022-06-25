#include<stdio.h>

int main()
{
	FILE* fp=fopen("asd.bin","wb");
	int a=1;
	char c='a';
	int q=2;
	char d='b';
	fwrite(&a,sizeof(int),1,fp);
	fwrite(&c,sizeof(char),1,fp);
	fwrite(&q,sizeof(int),1,fp);
	fwrite(&d,sizeof(char),1,fp);
	return 0;

}
