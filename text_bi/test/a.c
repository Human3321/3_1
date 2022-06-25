#include<stdio.h>

int main()
{
	FILE* fp=fopen("asd.bin","rb");
	int count=0;
	int i=0;
	char a[2];
	int b[2];
	for(i=0;i<2;i++)
	{
	

		fread(&b[count],sizeof(char),1,fp);
	fread(&a[count],sizeof(int),1,fp);
	//	fread(&b[count],sizeof(char),1,fp);
		count++;		
	}
	return 0;
}
