#include <stdio.h>
#include <string.h>

// 기본값 
// MIN_LENGTH 300
// MAX_LENGTH 200

#define MIN_LENGTH		300
#define MAX_LENGTH		100
#define MAX_STRLEN		1500

char strLine[350000][MAX_STRLEN];

void itoa(int, char*);
void tempFunction(char*, int);

int main(void) {
	// 변수 선언부 
	char buffer[MAX_STRLEN] = {' ',}; // 파일에서 문자열 받는 임시 버퍼 

	char str[10]; // 파일 이름 숫자부 임시 저장 변수 "12212".txt 

	FILE *fp; // 파일 변수 
	
	int i = 0, j = 0, k = 0;
	int total = 0; // 총 배열의 크기 저장 

	int stack = 0; // 각 파일당 들어갈 배열 수 스택 
	int length = 0; // 각 파일당 들어갈 문자열 총 길이 
	
	// 실제 작동부
	// 파일 읽기 
	if ((fp = fopen("test.txt", "rt")) == NULL) {
		printf("파일 읽기 오류");
		return 0;
	}
	
	// 파일이 끝나지 않는 동안 실행
	for (;!feof(fp);i++) {
		fgets(buffer, sizeof(buffer), fp); // 파일을 읽어서 buffer에 저장 

		strcpy(strLine[i], buffer); // 변수의 i번째 번지에 저장 

		if (i%100 == 0) {
			printf("%s ( %d )\n", strLine[i], i);
		}
	}
	
	// 총 배열의 크기 저장 
	total = i;
	
	i = 0;
	
	// 임시 파일 변수 닫기 
	fclose(fp);
	
	for(;i<total;i++) {
		if (strlen(strLine[i]) > MAX_LENGTH) {
			char temp[MAX_STRLEN] = {' ',};
			
			strncpy(temp, strLine[i], MAX_LENGTH);
			
			tempFunction(strLine[i], MAX_LENGTH);
			
			strLine[i][strlen(strLine[i])-1] = '\n';
			
			strcat(strLine[i], strLine[i+1]);
			strcpy(strLine[i+1], strLine[i]);
			
			strcpy(strLine[i], temp);
		}
	}
	
	i = 0;
	
	char* fileName = (char *)malloc(strlen("1.txt")+10); // malloc으로 할당 
	strcpy(fileName, "1.txt"); // 파일 이름 선저장 
	
	for (;i < total;i += stack) {
		if ((fp = fopen(fileName, "w")) == NULL) {
			printf("파일 읽기 오류");
			break;
		}
		
		stack = 0;
		length = 0;
		
		for (;;) {
			if (length >= MIN_LENGTH) {
				for(k=0;k<stack;k++) {
					if (strcmp(strLine[i+k], "\n") != 0 && strcmp(strLine[i+k], " \n") != 0) {
						fputs(strLine[i+k], fp);
					}
				}
				break;
			} else {
				length += strlen(strLine[i+stack]);
				stack++;
			}
		}

		j += 1;
		
		itoa(j, str);
    
		fileName = strcat(str, ".txt");
		
		if (j%1000 == 0) {
			printf("%s %s ", fileName, strLine[i]);
			printf("( %d )\n", length);
		}
		
		fclose(fp);
	}
	
	fclose(fp);
	
	printf("총 %d개의 파일을 생성했습니다. 프로그램은 5초 뒤에 종료됩니다.", j);
	
	sleep(5);
	
	return 0;
}

void itoa(int num, char *str) {
    int i = 0;
    int radix = 10;  // 진수
    int deg = 1;
    int cnt = 0;

    while(1) {    // 자리수의 수를 뽑는다
        if((num/deg) > 0)
            cnt++;
        else
            break;
        deg *= radix;
    }

    deg /= radix;    // deg가 기존 자리수보다 한자리 높게 카운트 되어서 한번 나누어줌 
    // EX) 1241 ->    cnt = 4; deg = 1000;

    for(i=0;i<cnt;i++) {    // 자리수만큼 순회
        *(str+i) = num/deg + '0';    // 가장 큰 자리수의 수부터 뽑음
        num -= ((num/deg) * deg);        // 뽑은 자리수의 수를 없엠
        deg /= radix;    // 자리수 줄임
    }
    
    *(str+i) = '\0';  // 문자열끝널..
}

void tempFunction(char* ori, int a) {
	int j = 0;
	char result[MAX_STRLEN] = { ' ', };
	
	for (j = 0; j < (strlen(ori) - a); j++) {
		*(ori+j) = ori[a + j];
	}
	
	*(ori+j) = '\0';
}

