#include<stdio.h> //기본 함수
#include<stdlib.h>//exit사용
#include<string.h>//str함수 사용

//수정 부분에서 내용을 구조체로 관리
struct temp{
	char ch[256];
};

int mail_check(char mail[]) //메일의 오류를 확인하는 함수
{
	int n_count=0,dot_count=0; //@의 개수와 .의 개수를 확인하는 변수
	char* n_num; //@의 위치를 확인하는 포인터
	char* dot_num; //.의 위치를 확인하는 포인터
	char* pch=mail; //매개변수가 가리키는 위치를 pch도 가르키게 선언

	while(pch != NULL) //pch가 NULL이 아닐때 반복
	{
		pch=strchr(pch,'.');//pch가 가리키는 값에서 .을 찾아서 그 포인터는 pch로 삽입
		if(pch!=NULL)//만약 .이 없으면 pch는 NULL을 가리켜서 안의 코드가 작동하지 않음
		{
			pch++; //처음으로 찾은 .의 다음 포인터를 가리킴/ .의 개수를 확인하기 위함
			dot_count++; //dot의 개수를 증가
			dot_num=pch; //제일 마지막에 나온 .의 포인터가 dot_num에 저장됨
		}
	}
	pch=mail; //위에 실행되서 pch는 NULL값이 되었으므로 다시 매개변수의 포인터를 삽입
	while(pch != NULL) 
	{
		pch=strchr(pch,'@');
		if(pch!=NULL)
		{
			pch++;
			n_count++;
			n_num=pch;
		}
	}
	//위와 동일하게 구현
	if(n_count==1&&dot_count==1&&(dot_num-n_num>0)) //@가 1개이고 .이 한개이며 .이 @보다 뒤에 있을 경우 / 배연의 포인터는 연속되므로 뒤에 있을수록 포인터의 크기가 크다
		return 1;
	else
		return 0;
}

void save() //새로운 사람을 저장하는 함수
{
	FILE *fp=fopen("date.txt","a"); // 같은 위치에 있는 date.txt파일을 추가모드로 염
	if(fp==NULL)//오류 처리
		fprintf(stderr,"error\n");
	char name[256]={0}; // 이름을 저장하는 변수
	int age; //나이를 저장하는 변수
	char mail[256]; //메일을 저장하는 변수
	char check={0};//계속 입력할 것인지 확인하기 위한 char변수
	while(1)
	{		
		printf("이름 : ");
		scanf(" %[^\n]s",name);//이름을 name에 저장 / 앞에 공백을 사용하여서 입력에 \n이 들어가는 것을 방지
		printf("나이 : ");
		scanf(" %d",&age);//나이를 age의 위치에 저장
		printf("이메일 : ");
		scanf(" %s",mail);//이메일을 mail에 저장
		if(age<=200&&(mail_check(mail)==1))//나이가 200이하이며 이메일의 구조가 맞을때
			fprintf(fp,"%s/%d/%s\n",name,age,mail);//파일에 이름과 나이 메일주소를 작성
		else
			printf("입력값에 오류가 있습니다.\n");
		while(1)// 계속 입력 유무를 묻는 함수
		{
			printf("계속 입력 할까요?(Y/N)\n");
			scanf(" %c",&check);//값을 check에 저장
			if(check=='N')//N입력시 반복문를 벗어남
			{
				printf("입력이 완료되었습니다.\n");
				break;
			}
			else if(check=='Y')//Y입력시 반복문을 벗어남
			{
				break;	
			}
			else//Y나 N이 아닌 다른경우를 입력할 경우 반복문에서 벗어나지 못함
			{}
		}
		if(check=='N')//N을 입력하여 반복문을 벗어났을 시 반복문을 벗어남
			break;
	}
	fclose(fp);//fp로 연 파일을 닫음 / 이때 파일이 저장됨
}

void modify() //수정모드
{
	FILE *fp = fopen("date.txt","r"); // date파일을 읽기모드로 염
	int count =0,check=0; //줄을 세는 변수 count와 사용자가 있는지 확인하는 변수 check를 선언
	int i=0; //반복문 변수 선언
	char buf[256];//파일에서 읽기위한 변수
	char name[256];//이름을 저장하기 위한 변수
	int age;//나이를 저장하기위한 변수
	char mail[256];//메일을 저장하기 위한 변수
	struct temp t[50];//구조체를 선언
	printf("수정할 회원의 이름을 입력 하시오: ");
	scanf(" %[^\n]s",name);
	while(fgets(buf,256,fp))//buf에 256의 크기로 fp경로의 파일을 열어서 한줄씩(\n까지)대입
	{
		if(strstr(buf,name)!=NULL)//strstr로 buf에 name의 문자열이 존재하는지 확인 / 존재하지 않으면 NULL값을 반환
			check++; // name이 파일에 존재하지 않는 경우 check는 0이 된다.
			//수정하기위해 입력받은 이름이 존재할 경우 t에 저장하기 않는다.
		else//fp의 파일을 읽어서 구조체t에 하나씩 대입
		{
			strcpy(t[count].ch,buf);// t[count].ch에 buf의 문자열을 복사한다.
			count++;//대입한 후 다음 배열로 이동하기 위한 변수
		}
	}
	if(check==0)//입력받은 name이 파일에 존재하지 않는 경우
		printf("사용자 %s 는 없습니다.\n",name);
	else//입력받은 name이 파일에 존재하는 경우
	{
		printf("사용자 %s 을 수정합니다.\n",name);
		printf("이름 : ");
		scanf(" %[^\n]s",name);
		printf("나이 : ");
		scanf(" %d",&age);
		printf("이메일 : ");
		scanf(" %s",mail);	
	} //각각에 맞는 값들을 입력 받는다.
	fclose(fp); //읽기모드 fp 종료
	if(check==1&&age<=200&&(mail_check(mail)==1)) //수정하기 위해 입력받은 name이 1개가 존재하며 나이 조건과 이메일 조건에 만족할때
	{
		fp=fopen("date.txt","w");//파일을 쓰기 모드로 연다.
		for(i=0;i<count;i++)
		{
			fprintf(fp,"%s",t[i].ch); //구조체 t에 저장한 값들을 파일에 작성
		}
		fprintf(fp,"%s/%d/%s\n",name,age,mail);//수정된 값들을 파일의 마지막에 넣는다.
	
		fclose(fp);//파일 종료
	}
	else//조건에 부합하지 않은 경우
		printf("입력값에 오류가 있습니다.\n");
}

void delete() //삭제기능
{
	FILE *fp = fopen("date.txt","r");//파일을 읽기 모드로 염
	int count =0; //파일의 줄을 확인하기 위한 변수
	int i=0;//반복문 사용 변수
	char buf[256];//파일을 읽기위한 buf
	char name[256];//이름을 입력받기 위한 값
	struct temp t[50];//파일의 줄들을 관리하기 위한 구조체 선언
	printf("삭제할 회원의 이름을 입력 하시오: ");
	scanf(" %[^\n]s",name);//[^\n]을 이용하여 scanf가 \n이 나올때까지 입력을 받음
	while(fgets(buf,256,fp))//fp경로의 파일을 buf에 256씩 읽어옴. 다 앍으면 NULL(0)반환
	{
		if(strstr(buf,name)==NULL)//buf에 name문자열이 존재하는기 확인하는 조건문 / NULL이라는 것은 name이 buf에 없는때 실행
		{
			strcpy(t[count].ch,buf); //buf에 name이 없을때 t에 buf의 값을 대입
			count++;//증가
		}
	}
	fclose(fp); //읽기모드 닫기

	fp=fopen("date.txt","w");//쓰기 모드로 열기
	for(i=0;i<count;i++)
	{
		fprintf(fp,"%s",t[i].ch);//파일에 t배열에 존재하는 값들을 대입
	}
	
	fclose(fp); //파일 닫기
	
}

void view()//전체 회원 보기
{
	FILE* fp =fopen("date.txt","r");//읽기 모드로 열기
	char buf[256];//한줄씩 읽기위한 버퍼
	while(fgets(buf,256,fp))//한줄씩 파일을 읽음
	{
		printf("%s",buf);//buf의 내용을 출력
	}
	fclose(fp);//파일 닫기
}



int main()
{
	int num;
	while(1)//디스플레이
	{
		printf("1. 신규회원 저장\n");
       		printf("2. 회원정보 수정\n");
        	printf("3. 회원삭제\n");
	        printf("4. 모든 회원 리스트\n");
		printf("5. 졸요\n");
		printf("입력하시오 >");
        	scanf("%d",&num);
		if(num == 1)
			save();
		else if(num ==2)
			modify();
		else if(num ==3)
			delete();
		else if(num ==4)
			view();
		else if(num==5)
			exit(0);
	}
	return 0;

}


