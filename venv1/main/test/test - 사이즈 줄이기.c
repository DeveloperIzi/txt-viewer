#include <stdio.h>
#include <string.h>

#define MAX_LENGTH		50
#define MAX_STRLEN		1000

void itoa(int, char*);
void tempFunction(char*, int);

char strLine[1000][MAX_STRLEN]; // ���� ���� 

int main(void) {
	char buffer[MAX_STRLEN] = {' ',}; // ���Ͽ� �ִ� �� ���� �ӽ÷� ���� ���� 

	char str[10]; // ���� �̸� �ӽ� ���� ���� 

	FILE* fp; // ���� ������ 

	int i = 0;
	int total = 0; // �� ������ ������ ������ ���� 

	if ((fp = fopen("test.txt", "rt")) == NULL) { // ���� �б� 
		printf("���� �б� ����");
		return 0;
	}

	while (!feof(fp)) { // ������ ������ �ʾҴٸ� 
		fgets(buffer, sizeof(buffer), fp); // ������ �о buffer�� ���� 

		strcpy(strLine[i], buffer); // ������ i��° ������ ���� 

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
	int radix = 10;  // ����
	int deg = 1;
	int cnt = 0;

	while (1) {    // �ڸ����� ���� �̴´�
		if ((num / deg) > 0)
			cnt++;
		else
			break;
		deg *= radix;
	}

	deg /= radix;    // deg�� ���� �ڸ������� ���ڸ� ���� ī��Ʈ �Ǿ �ѹ� �������� 
	// EX) 1241 ->    cnt = 4; deg = 1000;

	for (i = 0; i < cnt; i++) {    // �ڸ�����ŭ ��ȸ
		*(str + i) = num / deg + '0';    // ���� ū �ڸ����� ������ ����
		num -= ((num / deg) * deg);        // ���� �ڸ����� ���� ����
		deg /= radix;    // �ڸ��� ����
	}

	*(str + i) = '\0';  // ���ڿ�����
}

void tempFunction(char* ori, int a) {
	int j = 0;
	char result[MAX_STRLEN] = { ' ', };
	
	for (j = 0; j < (strlen(ori) - a); j++) {
		*(ori+j) = ori[a + j];
	}
	
	*(ori+j) = '\0';
}

