#include <stdio.h>
#include <string.h>

#define MAX_LENGTH		50
#define MAX_STRLEN		1000

void itoa(int, char*);
void tempFunction(char*, int);

char strLine[1000][MAX_STRLEN]; // 변수 설정 

int main(void) {
	char buffer[MAX_STRLEN] = {' ',}; // 파일에 있는 한 줄을 임시로 받을 변수 

	char str[10]; // 파일 이름 임시 저장 변수 

	FILE* fp; // 파일 포인터 

	int i = 0;
	int total = 0; // 총 파일의 개수를 저장할 변수 

	if ((fp = fopen("test.txt", "rt")) == NULL) { // 파일 읽기 
		printf("파일 읽기 오류");
		return 0;
	}

	while (!feof(fp)) { // 파일이 끝나지 않았다면 
		fgets(buffer, sizeof(buffer), fp); // 파일을 읽어서 buffer에 저장 

		strcpy(strLine[i], buffer); // 변수의 i번째 번지에 저장 

		total += strlen(strLine[i]);

		printf("%s ( %d, %d )\n", strLine[i], i, total);

		i++;
	}

	total = i;

	i = 0;

	fclose(fp);

	char* fileName = (char *)malloc(strlen("1.txt")+10);
	
	strcpy(fileName, "1.txt");
	
	puts("\n\n\n\n\n\n\n");
	
	for(;i<total;i++) {
		if (strlen(strLine[i]) > MAX_LENGTH) {
			char temp[MAX_STRLEN] = {' ',};
			
			strncpy(temp, strLine[i], MAX_LENGTH);
			
			tempFunction(strLine[i], MAX_LENGTH);
			
			strLine[i][strlen(strLine[i])-1] = ' ';
			
			strcat(strLine[i], strLine[i+1]);
			strcpy(strLine[i+1], strLine[i]);
			
			strcpy(strLine[i], temp);
		}
	}

	i = 0;
	
	for(;i<total;i++) {
		printf("%s\n", strLine[i]);
	}
	
	return 0;
}

void itoa(int num, char* str) {
	int i = 0;
	int radix = 10;  // 진수
	int deg = 1;
	int cnt = 0;

	while (1) {    // 자리수의 수를 뽑는다
		if ((num / deg) > 0)
			cnt++;
		else
			break;
		deg *= radix;
	}

	deg /= radix;    // deg가 기존 자리수보다 한자리 높게 카운트 되어서 한번 나누어줌 
	// EX) 1241 ->    cnt = 4; deg = 1000;

	for (i = 0; i < cnt; i++) {    // 자리수만큼 순회
		*(str + i) = num / deg + '0';    // 가장 큰 자리수의 수부터 뽑음
		num -= ((num / deg) * deg);        // 뽑은 자리수의 수를 없엠
		deg /= radix;    // 자리수 줄임
	}

	*(str + i) = '\0';  // 문자열끝널
}

void tempFunction(char* ori, int a) {
	int j = 0;
	char result[MAX_STRLEN] = { ' ', };
	
	for (j = 0; j < (strlen(ori) - a); j++) {
		*(ori+j) = ori[a + j];
	}
	
	*(ori+j) = '\0';
}

