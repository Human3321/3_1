#include <stdio.h> //기본적인 함수 사용 
#include <time.h>//time을 위해 사용
#include <stdlib.h>//rand를 사용하기 위함
#define NUM 6 // 로또 개수인 6개를 전역변수로 선언

void input(int set[]) // 배열에 난수값을 대입
{
	int i=0; // i값을 선언
	for(i=0;i<NUM;i++) //반복문을 이용하여 배열0~5에 대입
	{
		set[i]=rand()%45+1; // 난수값이 1~45
	}
}

int check(int set[]) // 삽입한 난수 값에 중복이 있는지 확인
{
	int temp; //비교하기 위한 변수
	int i,j; //반복문에 사용하는 변수
	for(i=0;i<NUM;i++) //배열의 첫번째부터 마지막, 두번째부터 마지막...
	{
		temp = set[i]; //temp에 i번째 값을 대입
		for(j=i+1;j<NUM;j++) // j는 i다음부터 배열 마지막까지의 값
		{
			if(temp==set[j]) // temp가뒤에 값과 같으면 1반환
				return 1;
		}
	}
	return 0; // 중복이 없으면 0 반환
}
void sort(int set[]) // 오름차순 정렬을 위한 함수
{
	int i,j,temp,least; //반복문에 사용할 변수 i,j와 임시값 temp,least를 선언
	for(i=0;i<NUM-1;i++) //첫번째부터 마지막,두번째부터 마지막...까지 반복
	{
		least=i; // 비교하기 위한 배열의 순서를 least에 대입
		for(j=i+1;j<NUM;j++) // least의 다음값부터 마지막까지 비교하기 위한 반복문
			if(set[j]<set[least]) // lieast번째가 j번째보다 배열의 값이 크면
				least=j; // least에는 j값을 대입
		temp=set[i];// temp에 i번째 값을 대입
		set[i]=set[least];//least번째 값(더 작음)을 비교하던 i번째 값에 대입
		set[least]=temp;//원래 i번째에 있던 값을 least번째 값에 대입
	}
}

int main()
{
	srand(time(NULL)); //진짜 난수값을 넣기 위한 라인
	int count; // 몇개읩 변호를 받는지 저장
	int i; // 반복문변수
	int set[NUM]; // 로또 번호를 저장하기 위한 변수
	printf("몇개의 숫자를 받겠습니까?: "); // 출력문
	scanf("%d",&count); // 입력받은 값을 count에 저장
	for(i=0;i<count;i++) //입력받은 반큼 반복
	{
		input(set); //input함수에 매개변수 set을 넣어서 호출
		while(check(set)) // 중복이 존재하면 새로운 수를 대입
			{
				input(set);
			}
		sort(set);//오름차순 정렬
		for(int j=0;j<NUM;j++) // 배열의 숫자를 출력하기 위한 반복문
			printf("%d ",set[j]);
		printf("\n");// 줄바꿈라인
	
	}
	return 0;
}
