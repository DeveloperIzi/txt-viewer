#include <stdio.h>
#include <string.h>
#include <direct.h>	//getcwd

#define MAX_PATH 260

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


int main(void) {
	int j = 0;
	
	char strBuffer[MAX_PATH] = {0,};
	char *pstrBuffer;
	char *fileName;
	char str[10];

	while (1) {
		j += 1;
		
		itoa(j, str);

		fileName = strcat(str, ".png");
		
		pstrBuffer = getcwd(strBuffer, MAX_PATH);
	
		strcat(pstrBuffer, "\\");
		strcat(pstrBuffer, fileName);
		
		// remove(pstrBuffer);
		
		if (remove(pstrBuffer) == -1) {
			// break;
		}
		
		if (j%1000 == 0) {
			printf("%s ", fileName);
			printf("( %d )\n", j);
		}
	}
	
	printf("�� %d���� ������ �����߽��ϴ�. ���α׷��� 5�� �ڿ� ����˴ϴ�.", j);
	
	sleep(5);
	
	return 0;

}
