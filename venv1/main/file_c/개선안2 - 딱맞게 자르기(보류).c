#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)

typedef struct strLine {
	char strLine[1000];
} line_str;

void itoa(int, char*);
char* tempFunction(char*, int);

line_str strLine[89000]; // ���� ���� 

int main(void) {
	char buffer[1000]; // ���Ͽ� �ִ� �� ���� �ӽ÷� ���� ���� 

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

		strcpy(strLine[i].strLine, buffer); // ������ i��° ������ ���� 

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
			printf("���� �б� ����");
			break;
		}

		stack = 0;
		length = 0;

		for (;;) {
			if (length >= 400) {
				if (length >= 500) {
					// ��ģ �� �κ��� �ڷ� �ѱ�� �ڵ� �ۼ�

					if (length >= 800) {
						printf("\n\n���: ������ ������ ����� ���� �߰��߽��ϴ� ( %d )\n", j);
					}

					char* temp;
					temp = tempFunction(strLine[i + stack - 1].strLine, strlen(strLine[i + stack - 1].strLine) - (length - 500));

					strcat(temp, strLine[i + stack].strLine);
					strcpy(strLine[i + stack].strLine, temp);

					// �ڸ��� 
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

	printf("�� %d���� ������ �����߽��ϴ�. ���α׷��� 5�� �ڿ� ����˴ϴ�.", j);

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

char* tempFunction(char* ori, int a) {
	int j = 0;
	char result[1000] = { ' ', };
	for (j = 0; j < a; j++) {
		result[j] = ori[a + j];
	}

	return result;
}

