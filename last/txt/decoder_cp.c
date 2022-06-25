#include<stdio.h>
#include<string.h>

int friend_count_N=1;

void star_printf(FILE* n,int count)
{
	if(count==0)
		fprintf(n,"%s","*USER STATUS*");
	else if(count==1)
		fprintf(n,"%s","*ITEMS*");
	else if(count==2)
		fprintf(n,"%s","*FRIENDS LIST*");
	else if(count==3)
		fprintf(n,"%s","*DESCRIPTION*");
}


void name_print(FILE* n,int star,int count)
{
	if(star==1)
	{
		if(count==0)
			fprintf(n,"%s","ID: ");
		else if(count==1)
			fprintf(n,"%s","NAME: ");
		else if(count==2)
			fprintf(n,"%s","GENDER: ");
		else if(count==3)
			fprintf(n,"%s","AGE: ");
		else if(count==4)
			fprintf(n,"%s","HP: ");
		else if(count==5)
			fprintf(n,"%s","MP: ");
		else if(count==6)
			fprintf(n,"%s","COIN: ");
	}
}

void friend_print(FILE* n,int count)
{	
	if(count==0)
		fprintf(n,"%s%d %s","FRIEND",friend_count_N,"ID: ");
	else if(count==1)
		fprintf(n,"%s%d %s","FRIEND",friend_count_N,"NAME: ");	
	else if(count==2)
		fprintf(n,"%s%d %s","FRIEND",friend_count_N,"GENDER: ");
	else if(count==3)
		fprintf(n,"%s%d %s","FRIEND",friend_count_N,"AGE: ");
	else if(count==4)
	{}	
}

void decode(char input[],char output[])
{
	int line_count=0,qqone_read_line,one_read_count;
	int char_count=0;
	int i=0,j;
	int section=-1;
	int check1=0,check2=0,check3=0;
	int star_count=0,set_count=0,friend_count=0;
	int one_read_line[2]={0, };
	char buf[256];
	FILE* rp=fopen(input,"r");
	while(fgets(buf,256,rp))
	{
	//	line_count++;
		one_read_line[i]++;
		if(strcmp(buf,"^\n")==0)
			i++;
		char_count+=strlen(buf);
	}

	fclose(rp);
//	printf("%d %d %d",one_read_line[0],one_read_line[1],one_read_line[2]);
	printf("%d",char_count);
//	printf("%d %d\n",line_count,char_count);
//	one_read_line=line_count/3;
	one_read_count=(char_count/3);
	char compare[3][one_read_count];
	char result[one_read_count];
	rp=fopen(input,"r");

	for(i=0;i<3;i++)
	{
		for(j=0;j<one_read_line[i];j++)
		{
			fgets(buf,256,rp);
			strcat(compare[i],buf);
		}

//	printf("%s",compare[i]);
	}

	fclose(rp);
//	printf("%s",compare[2]);
	FILE* wp=fopen(output,"w");
	for(i=0;i<one_read_count;i++)
	{	
		if((compare[0][i]==compare[1][i])&&(compare[1][i]==compare[2][i]))
		//3개가 다 같은 경우
		{
			if(compare[0][i]=='@')
			{
				star_printf(wp,star_count);
				star_count++;
			}
			else if(compare[0][i]=='*')
			{
	//			fprintf(wp,"%s","\n");
			}
			else
			{
				if(compare[0][i]=='\n'&&star_count==3&&(compare[0][i+1]!='@'))
				{
					fprintf(wp,"%c",compare[0][i]);
					friend_print(wp,friend_count);
					friend_count++;
					if(friend_count==5)
					{
						friend_count_N++;
						friend_count=0;
					}
				}
				else if(compare[0][i]=='\n')
				{
					fprintf(wp,"%c",compare[0][i]);
					name_print(wp,star_count,set_count);
					set_count++;
				}

				else
					fprintf(wp,"%c",compare[0][i]);
			}
			section=0;
		}

		/*
		else if((compare[0][i]==compare[1][i])&&(compare[1][i]!=compare[2][i]))
		//0,1이 같고 1,2가 다른경우 -> 2번째에 오류가 발생
		{

			if(compare[0][i]=='@')
			{
				star_printf(wp,star_count);
				star_count++;
			}
			else if(compare[0][i]=='*')
			{
	//			fprintf(wp,"%s","\n");
			}
			else
			{
				if(compare[0][i]=='\n'&&star_count==3&&(compare[0][i+1]!='@'))
				{
					fprintf(wp,"%c",compare[0][i]);
					friend_print(wp,friend_count);
					friend_count++;
					if(friend_count==5)
					{
						friend_count_N++;
						friend_count=0;
					}
				}
				else if(compare[0][i]=='\n')
				{
					fprintf(wp,"%c",compare[0][i]);
					name_print(wp,star_count,set_count);
					set_count++;
				}

				else
					fprintf(wp,"%c",compare[0][i]);
			}
			section=2;
		}
		else if((compare[0][i]==compare[2][i])&&(compare[0][i]!=compare[1][i]))
		//0,2가 같고 0,1이 다른경우 ->1번째에 오류가 발생	
		{
	
			if(compare[0][i]=='@')
			{
				star_printf(wp,star_count);
				star_count++;
			}
			else if(compare[0][i]=='*')
			{
	//			fprintf(wp,"%s","\n");
			}
			else
			{
				if(compare[0][i]=='\n'&&star_count==3&&(compare[0][i+1]!='@'))
				{
					fprintf(wp,"%c",compare[0][i]);
					friend_print(wp,friend_count);
					friend_count++;
					if(friend_count==5)
					{
						friend_count_N++;
						friend_count=0;
					}
				}
				else if(compare[0][i]=='\n')
				{
					fprintf(wp,"%c",compare[0][i]);
					name_print(wp,star_count,set_count);
					set_count++;
				}

				else
					fprintf(wp,"%c",compare[0][i]);
			}
			section=2;
		}
		else if((compare[1][i]==compare[2][i])&&(compare[0][i]!=compare[1][i]))
		//1,2가 같고 0,1이 다른경우 ->0번째에 오류가 발생	
		{
				
			if(compare[1][i]=='@')
			{
				star_printf(wp,star_count);
				star_count++;
			}
			else if(compare[1][i]=='*')
			{
	//			fprintf(wp,"%s","\n");
			}
			else
			{
				if(compare[1][i]=='\n'&&star_count==3&&(compare[1][i+1]!='@'))
				{
					fprintf(wp,"%c",compare[1][i]);
					friend_print(wp,friend_count);
					friend_count++;
					if(friend_count==5)
					{
						friend_count_N++;
						friend_count=0;
					}
				}
				else if(compare[1][i]=='\n')
				{
					fprintf(wp,"%c",compare[1][i]);
					name_print(wp,star_count,set_count);
					set_count++;
				}

				else
					fprintf(wp,"%c",compare[1][i]);
			}
			section=1;
		}
		*/
		else
			printf("중복된 곳에서 에러가 발생\n");

		if(section==1)
			printf("원본 데이터에 문제가 발생, 복구 완료\n");
		else if(section==2)
			printf("복구용 데이터에 문제가 발생, 복구 완료\n");
		else
		{}
	}
//	fprintf(wp,"%s",result);
	fclose(wp);


	printf("%d",set_count);
}

int main(int argc,char* argv[])
{
	if(argc==3)
		decode(argv[1],argv[2]);
	else
		printf("./decoder.out \"복원할 파일\" \"생성된 파일\"\n");
	
	return 0;
}
