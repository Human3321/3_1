#include<stdio.h>
#include<string.h>

int str_count(char *input) //analysis에서 변수와 함수의 길이를 반환하는 함수
{
	char* p; //포인터 선언
	p=strstr(input," ");//p의 위치는 input에서 첫 " "의 위치
	p=strstr(p+1," "); //p의 위치는 input에서 두번째 " "의 위치

	return strlen(input)-strlen(p)+1; //input의 길이에서 input의 두번째 " "까지의 길이를 뺌 -> input의 시작에서 두번째 " "의 길이
}

void funa(char cmd[]) //매개변수가 1개인 함수
{
	if(strcmp(cmd,"-help")==0) // cmd가 -help일때
		printf("사용방법\n"); //구현한 기능들을 출력
		printf("-list \"문서이릅\": 문서의 내용을 출력.\n");
		printf("-linecount \"문서이름\": 문서의 라인을 출력.\n");
		printf("-replace \"문서이름\" \"변경전단어\" \"변경후단어\": 변경전단어를 변경후 단어로 교체\n");
		printf("-analysis \"문서이름\": 문서에 사용된 변수와 함수의 갯수와 이름을 출력.\n");
}

void funb(char cmd[],char flie[]) //매개변수가 2개인 함수
{
	FILE* fp=fopen(flie,"r"); //입력받은 file을 읽기모드로 오픈
	char buf[256]; // 파일에서 추출한 문자열을 담을 공간
	if(fp==NULL) //file이 존재하지 않을때
		fprintf(stderr,"error"); //오류처리
	if(strcmp(cmd,"-list")==0)//cmd가 -list일때
	{
		while(fgets(buf,256,fp)) //파일에서 한줄씩 buf에 담는다. 다 담으면 NULL을 반환
		{
			printf("%s",buf); //buf를 출력
		}
		fclose(fp); //fp의 파일을 닫음
	}
	else if(strcmp(cmd,"-linecount")==0) // cmd가 -linecount일때
	{
		int count=0; //count변수 선언
		while(fgets(buf,256,fp)) //fp의 파일을 한줄씩 읽음
		{
			count++; //count증가
		}
		printf("총 %d 라인으로 구성되어 있습니다.\n",count); //count는 파일의 한줄마다 하나식 증가
		fclose(fp);//파일 닫기
	}
	else if(strcmp(cmd,"-analysis")==0)//cmd가 -analysis일때
	{
		int var_count=0; //변수 카운터
		int value_count=0; //함수 카운터
		int i; //반복문을 위한 변수
		char *p; //중간에 찾은 문자열을 저장할 포인터 변수
		char var_name[10][256]; //변수 문자열을 저장할 배열을 2차원으로 선언
		char value_name[10][256]; //함수 문자열을 저장할 배열을 2차원으로 선언 
		while(fgets(buf,256,fp)) //fp의 파일을 한줄씩 읽어서 buf에 저장
		{
			if((p=strstr(buf,"int "))!=NULL&&strstr(buf,";")!=NULL) //buf에 int 가 포함되며 ;가 포함되면 -> 변수는 자료형 선언뒤에 한칸 띄우고 마지막에 세미콜론으로 종료 -> int형 변수이면
			{
				strncpy(var_name[var_count++],p,str_count(p));	// var_name배열에 p를 str_count(p)만큼 저장 -> p는 int 의 주소이며(앞에 공백이 있을시 buf와 주소가 다름)  str_count(p)는 p의 두번째 " "의 주소(첫번째 " " 는 int다음에 존재)
			}
			else if((p=strstr(buf,"double "))!=NULL&&strstr(buf,";")!=NULL) //buf에 double 가 존재하며 ;가 존재 -> double형의 변수를 판별
			{
				strncpy(var_name[var_count++],p,str_count(p));	//그 라인을 변수 문자열 저장곤간인 var_name에 저장
			}
			else if((p=strstr(buf,"void "))!=NULL&&strstr(buf,"(")!=NULL&&strstr(buf,")")!=NULL) //buf에 void 와 (,)가 존재하면 -> void형 함수를 찾음
			{
				strncpy(value_name[value_count++],p,str_count(p)); //함수 저장공간인 value_name에 저장
			}
		}
		printf("본 소스 코드에서 아용된 변수는 %d개입니다.\n",var_count); //변수의 개수 출력
		for(i=0;i<var_count;i++) // 변수의 개수만큼 반복
			printf("%s\n",var_name[i]); //문자열에 저장된 변수의 이름을 출력
		printf("\n");
		printf("본 소스 코드에서 아용된 함수는 %d개입니다.\n",value_count); //함수의 개수 출력
		for(i=0;i<value_count;i++) //함수의 개수만큼 반복
			printf("%s\n",value_name[i]);//함수 이름 출력
		printf("\n");
			
	}
}

void func(char cmd[],char file[],char before[],char after[])  //매개변수가 4개인 함수
{
	if(strcmp(cmd,"-replace")==0) //cmd가 -replace이면
	{
		FILE* fp=fopen(file,"r"); //file을 읽기모드로 작성
		FILE* tem=fopen("tem.txt","w");//임시 파일인 tem.txt를 생성하고 쓰기모드로 오픈
		char buf[256]; //문자열을 저장할 버퍼
		char before_n[256];//before문을 복사하여 사용할 문자열
		char* p; //조건에 맞는 문자열 포인터를 저장할 변수
		char* tem_buf; //버퍼의 위치를 포인터 위치로 변환하기 위한 변수
		int count=0; //바뀐 문자를 카운트하는 변수
		int i=0; //반복문에 사용할 변수
		strcpy(before_n,before); //before_n에 before의 내용을 복사
		strcat(before_n," "); //before_n에 " "을 추가 ->현재 before_n은 'before_n '
		while(fgets(buf,256,fp)) //fp에서 한줄씩 buf에 256개씩 삽입
		{
			if((p=strstr(buf,before_n))!=NULL) //p는 buf에서 before_n이 존재하지 않으면 NULL, p는 before_n문자열이 시작하는 위치
			{
				tem_buf=buf; //tem_buf에 buf의 위치를 삽입
				while(tem_buf!=p) //tem_buf의 위치가 p문자열이 아니면 반복문 실행-> 앞에 널문자를 살리기 위해 만듦
				{
					fprintf(tem,"%c",*tem_buf); //*tem_buf는 tem_buf가 가리키는 하나의 문자. tem파일에 문자를 삽입
					tem_buf++; //tem_buf은 다음 문자를 가리키는 포인터가 됨
				}
				fprintf(tem,"%s",after); //바꾼 문자열을 삽입
				fprintf(tem,"%s",p+strlen(before)); //바꾼 문자열을 삽입하고 바꾸기 전 문자열의 크기만큼 더하여서 바꾸기 전의 문자열을 뛰어 넘음
				count++; //바뀐 횟수 카운트
			}	
			else //buf에 before_n의 내용이 없으면
			{
				fprintf(tem,"%s",buf); //줄 전체를 tem에 작성
			}
			
		}
		fclose(fp); //fp 닫기
		fclose(tem);//tem 닫기
		fp=fopen(file,"w"); //fp를 file의 쓰기모드로 선언
		tem=fopen("tem.txt","r"); //tem을 tem.txt를 읽기모드로 선언
		while(fgets(buf,256,tem)) //tem의 내용을 한줄씩 256크기로 buf에 읽음
		{
			fprintf(fp,"%s",buf); //내용을 fp로 작성
		}
		fclose(fp); //파일 닫기
		fclose(tem); //파일 닫기
		remove("tem.txt"); //임시파일로 생성한 tem.txt를 삭제
		
		printf("총 %d개의 %s가 %s로 교체되었습니다.\n",count,before,after); //바뀐 횟수, 바꾸기전 문자열, 마꾼 후 문자열을 출력
		funb("-list","analysis.c"); //변경된 내용을 출력
	}
}

int main(int argc,char* argv[])
{
	//매개변수의 개수인 argc의 개수에 따라서 실행할 함수들을 선언
	if(argc==1)
		printf("옵션을 입력하시오.\n");
	else if(argc==2)
		funa(argv[1]);
	else if(argc==3)
		funb(argv[1],argv[2]);
	else if(argc==5)
		func(argv[1],argv[2],argv[3],argv[4]);
	return 0;

}
