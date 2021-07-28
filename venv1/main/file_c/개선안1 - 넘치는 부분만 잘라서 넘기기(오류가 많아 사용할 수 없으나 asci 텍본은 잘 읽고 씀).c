#include <stdio.h>
#include <string.h>

// �⺻�� 
// MIN_LENGTH 300
// MAX_LENGTH 200

#define MIN_LENGTH		300
#define MAX_LENGTH		100
#define MAX_STRLEN		1500

char strLine[350000][MAX_STRLEN];

void itoa(int, char*);
void tempFunction(char*, int);

int main(void) {
	// ���� ����� 
	char buffer[MAX_STRLEN] = {' ',}; // ���Ͽ��� ���ڿ� �޴� �ӽ� ���� 

	char str[10]; // ���� �̸� ���ں� �ӽ� ���� ���� "12212".txt 

	FILE *fp; // ���� ���� 
	
	int i = 0, j = 0, k = 0;
	int total = 0; // �� �迭�� ũ�� ���� 

	int stack = 0; // �� ���ϴ� �� �迭 �� ���� 
	int length = 0; // �� ���ϴ� �� ���ڿ� �� ���� 
	
	// ���� �۵���
	// ���� �б� 
	if ((fp = fopen("test.txt", "rt")) == NULL) {
		printf("���� �б� ����");
		return 0;
	}
	
	// ������ ������ �ʴ� ���� ����
	for (;!feof(fp);i++) {
		fgets(buffer, sizeof(buffer), fp); // ������ �о buffer�� ���� 

		strcpy(strLine[i], buffer); // ������ i��° ������ ���� 

		if (i%100 == 0) {
			printf("%s ( %d )\n", strLine[i], i);
		}
	}
	
	// �� �迭�� ũ�� ���� 
	total = i;
	
	i = 0;
	
	// �ӽ� ���� ���� �ݱ� 
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
	
	char* fileName = (char *)malloc(strlen("1.txt")+10); // malloc���� �Ҵ� 
	strcpy(fileName, "1.txt"); // ���� �̸� ������ 
	
	for (;i < total;i += stack) {
		if ((fp = fopen(fileName, "w")) == NULL) {
			printf("���� �б� ����");
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
	
	printf("�� %d���� ������ �����߽��ϴ�. ���α׷��� 5�� �ڿ� ����˴ϴ�.", j);
	
	sleep(5);
	
	return 0;
}

void itoa(int num, char *str) {
    int i = 0;
    int radix = 10;  // ����
    int deg = 1;
    int cnt = 0;

    while(1) {    // �ڸ����� ���� �̴´�
        if((num/deg) > 0)
            cnt++;
        else
            break;
        deg *= radix;
    }

    deg /= radix;    // deg�� ���� �ڸ������� ���ڸ� ���� ī��Ʈ �Ǿ �ѹ� �������� 
    // EX) 1241 ->    cnt = 4; deg = 1000;

    for(i=0;i<cnt;i++) {    // �ڸ�����ŭ ��ȸ
        *(str+i) = num/deg + '0';    // ���� ū �ڸ����� ������ ����
        num -= ((num/deg) * deg);        // ���� �ڸ����� ���� ����
        deg /= radix;    // �ڸ��� ����
    }
    
    *(str+i) = '\0';  // ���ڿ�����..
}

void tempFunction(char* ori, int a) {
	int j = 0;
	char result[MAX_STRLEN] = { ' ', };
	
	for (j = 0; j < (strlen(ori) - a); j++) {
		*(ori+j) = ori[a + j];
	}
	
	*(ori+j) = '\0';
}

