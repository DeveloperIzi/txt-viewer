#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)

typedef struct strLine {
	char strLine[1000];
} line_str;

void itoa(int, char*);
char* tempFunction(char*, int);

line_str strLine[89000]; // 변수 설정 

int main(void) {
	char buffer[1000]; // 파일에 있는 한 줄을 임시로 받을 변수 

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

		strcpy(strLine[i].strLine, buffer); // 변수의 i번째 번지에 저장 

		if (i % 100 == 0) {
			printf("%s ( %d )\n", strLine[i].strLine, i);
		}

		i++;
	}

	total = i;

	i = 0;

	fclose(fp);

	char* fileName = (char*)"1.txt";

	i = 0;
	int j = 0, k = 0;
	int stack = 0;
	int length = 0;

	while (i < total) {
		if ((fp = fopen(fileName, "w")) == NULL) {
			printf("파일 읽기 오류");
			break;
		}

		stack = 0;
		length = 0;

		for (;;) {
			if (length >= 400) {
				if (length >= 500) {
					// 넘친 뒷 부분을 뒤로 넘기는 코드 작성

					if (length >= 800) {
						printf("\n\n경고: 범위를 현저히 벗어나는 값을 발견했습니다 ( %d )\n", j);
					}

					char* temp;
					temp = tempFunction(strLine[i + stack - 1].strLine, strlen(strLine[i + stack - 1].strLine) - (length - 500));

					strcat(temp, strLine[i + stack].strLine);
					strcpy(strLine[i + stack].strLine, temp);

					// 자르기 
					strncpy(temp, strLine[i + stack - 1].strLine, strlen(strLine[i + stack - 1].strLine) - (length - 500));
					strcpy(strLine[i + stack - 1].strLine, temp);
				}

				for (k = 0; k < stack; k++) {
					if (strcmp(strLine[i + k].strLine, "\n") != 0) {
						fputs(strLine[i + k].strLine, fp);
					}
				}
				break;
			}
			else {
				length += strlen(strLine[i + stack].strLine);
				stack++;
			}
		}

		i += stack;
		j += 1;

		itoa(j, str);

		fileName = strcat(str, ".txt");

		if (j % 1000 == 0) {
			printf("%s %s ", fileName, strLine[i].strLine);
			printf("( %d )\n", length);
		}

		fclose(fp);
	}

	fclose(fp);

	printf("총 %d개의 파일을 생성했습니다. 프로그램은 5초 뒤에 종료됩니다.", j);

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

char* tempFunction(char* ori, int a) {
	int j = 0;
	char result[1000] = { ' ', };
	for (j = 0; j < a; j++) {
		result[j] = ori[a + j];
	}

	return result;
}

