#include <stdio.h>
#include <string.h>
#include <direct.h>	//getcwd

#define MAX_PATH 260

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
	
	printf("총 %d개의 파일을 삭제했습니다. 프로그램은 5초 뒤에 종료됩니다.", j);
	
	sleep(5);
	
	return 0;

}
