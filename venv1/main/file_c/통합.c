#include <stdio.h>
#include <string.h>

typedef struct strLine {
   char strLine[1000];
} line_str;

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

line_str strLine[89000];

int main(void) {
	char buffer[1000];

	char str[10];

	FILE *fp;
	
	int i = 0;
	int total = 0;
	
	if ((fp = fopen("test.txt", "rt")) == NULL) {
		printf("���� �б� ����");
		return 0;
	}
	
	while(!feof(fp)) {
		fgets(buffer, sizeof(buffer), fp);
		
		strcpy(strLine[i].strLine, buffer);
		
		if (i%100 == 0) {
			printf("%s ( %d )\n", strLine[i].strLine, i);
		}
		
		i++;
	}
	
	total = i;
	
	i = 0;
	
	fclose(fp);
	
	char* fileName = "1.txt";
	
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
			if (length >= 300) {
				for(k=0;k<stack;k++) {
					if (strcmp(strLine[i+k].strLine, "\n") != 0) {
						fputs(strLine[i+k].strLine, fp);
					}
				}
				break;
			} else {
				length += strlen(strLine[i+stack].strLine);
				stack++;
			}
		}

		i += stack;
		j += 1;
		
		itoa(j, str);
    
		fileName = strcat(str, ".txt");
		
		if (j%1000 == 0) {
			printf("%s %s ", fileName, strLine[i].strLine);
			printf("( %d )\n", length);
		}
		
		fclose(fp);
	}
	
	fclose(fp);
	
	printf("�� %d���� ������ �����߽��ϴ�. ���α׷��� 5�� �ڿ� ����˴ϴ�.", j);
	
	sleep(5);
	
	return 0;
}
