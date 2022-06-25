#include<stdio.h> //기본 함수 사용
#include<string.h> //문자열 함수 사용

struct Data{ //플레이어 정보를 구조체로 선언
	char name[256]; //ID, 255문자까지 입력 가능
	char age; //나이,-128~128까지 입력 가능
	unsigned short HP; //HP, 0~65535까지 입력 가능
	double x,y; //double형으로 소수 아래자기 입력 가능
	char friend[255][256];//동맹 리스트, 255개의 동맹 입력 가능
	int friend_count;//동맹의 수
};

void recoed() //플레이어 저장
{
	struct Data d; //데이터를 저장할 구조체 선언
	char file_name[260]; //파일의 이름을 저장할 문자열
	char check; //계속 입력을 받을지에 대한 문자 확인
	int i=0; //반복문 변수
	int len;//파일 이름의 길이를 저장할 변수
	d.friend_count=0; //선언한 구조체의 친구 수를 초기화
	printf("ID를 입력하세요: "); 
	scanf(" %s",d.name);
	printf("나이를 입력하세요: ");
	scanf(" %hhd",&d.age);
	printf("HP를 입력하세요: ");
	scanf(" %hd",&d.HP);
	printf("X좌표를 입력하세요:  ");
	scanf(" %le",&d.x);
	printf("Y좌표를 입력하세요: ");
	scanf(" %le",&d.y);
	//위까지 정보를 입력 받음
	while(1) //동맹 저장
	{
		printf("동맹 ID를 입력하세요: ");
		scanf(" %s",d.friend[d.friend_count++]); //구조체 d의 friend배열에 friend_count번째에 입력하고 frien_count 증가
		printf("동맹을 계속 추가할까요?: ");
		scanf(" %c",&check);
		if(check=='N') //N이면 반복문 탈출
			break;
		else if(check=='Y')//Y면 반복문 실행
		{}
		else //다른 문자열 입력시
		{
			while(!(check=='Y'||check=='N'))//Y또는N이 아니면 반복문 실행
			{
				printf("Y/N으로 입력해 주세요.\n");
				scanf(" %c",&check);
			}
			if(check=='Y') //Y인경우 반복문 다시 실행
			{}
			else//N인경우 탈출
				break;
		}
	}
	strcpy(file_name,d.name); //file_name에 d의 ID를 복사
	strcat(file_name,".bin"); //복사한 file_name에 .bin을 붙여서 파일명을 세팅
	len=strlen(file_name); //file_name의 길이를 len에 저장
	FILE* fp=fopen("DB.bin","ab"); //DB.bin파일을 바이너리 추가모드로 염
	fwrite(&len,sizeof(int),1,fp);//파일이름의 길이를 작성
	fwrite(file_name,sizeof(char),strlen(file_name),fp);//파일이름을 작성
	fclose(fp);//파일 닫기

	fp=fopen(file_name,"wb");//저장했던 file_name의 이름으로 바이너리 작성모드 실행

	fwrite(&d,sizeof(d),1,fp);//구조체 d를 바이너리로 작성
	fclose(fp);//파일 닫기

	printf("완료되었습니다.\n");

}

void all_print()
{
	struct Data d; //저장할 구조체 변수
	char file_name[260];//파일 이름 변수
	int file_len;//파일 길이 변수
	int i,j;//반복문 변수
	int count=0;//플레이어의 수
	int check_int[100]={0, };//int형 배열 초기화
	char check_char[100][256];//char형 배열 선언

	FILE* rp=fopen("DB.bin","rb"); //DB파일을 바이너리 읽기모드로 작성
	while(1)
	{
		fread(&check_int[count],sizeof(int),1,rp);//DB파일의 int형 숫자를 1개 check_int배열에 저장
		if(check_int[count]==0) //만약 읽은수가 0이면(없다면)
			break;//반복문 탈출
		fread(check_char[count],sizeof(char),check_int[count],rp);//DB파일을 이어서 길이수 만큼 char배열에 저장
		count++;//카운트 증가
	}
	fclose(rp);//파일 닫기
	printf("총 %d명의 플레이어가 기록되어 있습니다.\n",count); //플레이어 수 프린트
	for(j=0;j<count;j++)//카운트(플레이어 수)만큼 반복
	{
		printf("[플레이어%d]\n",j+1);
		FILE* p=fopen(check_char[j],"rb");//배열에 저장되었던 문자열의 파일을 파이너리 읽기모드로 오픈
		fread(&d,sizeof(d),1,p);//구조체를 읽어서 d에 저장
		fclose(p);//파일 닫기
	
		printf("ID : %s",d.name);
		printf(" / ");
		printf("나이: %hhd",d.age);
		printf(" / ");
		printf("HP : %hd",d.HP);
		printf(" / ");
		printf("좌표 : %.3lf , %.3lf",d.x,d.y);
		printf(" \n ");
		printf("등록된 동맹 수  : %d명",d.friend_count);
		printf("\n");
		for(i=0;i<d.friend_count;i++)
		{
			printf("%s",d.friend[i]);
			printf("\n");
		}
		//구조체 내용을 출력
	}
	printf("완료되었습니다.\n");

}

void file_remove()//파일 삭제
{
	char rm_name[260];//제거할 ID
	int i;//반복문 변수
	int count=0;//플레이어 카운트
	int check=-1;//제거할 ID가 존재하는지 확인하는 변수
	int check_int[100]={0, };//int형 배열 0으로 초기화
	char check_char[100][256];//char형 배열 선언

	FILE* rp=fopen("DB.bin","rb");//DB파일을 읽기모드로 오픈
	while(1)//반복문
	{
		fread(&check_int[count],sizeof(int),1,rp);//DB파일의 int형 크기만큼 1개를 읽어서 check_int[count]에 삽입 ->이 수는 뒤에 있는 문자열의 길이
		if(check_int[count]==0)//초기화한 값던 0이면
			break;//반복문 탈출
		fread(check_char[count],sizeof(char),check_int[count],rp);//char크기만큼 앞에 있던 check_int[count]만큼 읽어서 check_char[count]에 저장
		count++; //카운트 증가
	}
	fclose(rp);//파일 닫기
	printf("삭제할 ID를 입력하세요: ");
	scanf(" %s",rm_name);//삭제할 ID 입력
	strcat(rm_name,".bin");//파일 이름과 비교하기 위해서 rm_name에 .bin을 추가
	for(i=0;i<count;i++)//카운트만틈 반복
	{
		if(strcmp(rm_name,check_char[i])==0)//입력받은 rm_name과 check_char배열을 비교
			check=i; //전제하면 그 배열의 값을 check에 대입
	}
	if(check==-1)//입력받은 값이 존재하지 않으면 실행
		printf("해당 데이터는 존재하지 않습니다.\n");
	else //입력받은 값이 존재하면
	{
		FILE* fp=fopen("DB.bin","wb");//DB파일을 작성모드로 오픈
		for(i=0;i<count;i++)//카운트만틐 반복
		{	
			if(i==check) //중복된 check번째의 배열은
				continue;//작성하지 않고 반복문으로 회귀
			fwrite(&check_int[i],sizeof(int),1,fp);
			fwrite(check_char[i],sizeof(char),check_int[i],fp);
			//나머지 부분은 그대로 작성
		}
		fclose(fp);//파일 닫기
		remove(check_char[check]);//입력받은 파일 삭제
		printf("%s 삭제완료.\n",check_char[check]);	
	}

}

int main(int argc,char* argv[])
{
	int input;
	while(1)
	{
		printf("1. 신규 플레이어 정보 기록\n");
		printf("2. 기록된 모든 플레이어 정보 확인\n");
		printf("3. 플레이어 삭제\n");
		printf("4. 종료\n");
		printf("입력하세요> ");
		scanf("%d",&input);

		if(input==1)
			recoed();
		else if(input==2)
			all_print();
		else if(input==3)
			file_remove();
		else if(input==4)
			break;
	}
	return 0;
}
