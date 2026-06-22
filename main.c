#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

// 1. 로또 번호 생성 (중복 검사)
void generateLotto(int lotto[]) {
    int i, j;
    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        lotto[i] = rand() % 45 + 1;
        for (j = 0; j < i; j++) { 
            if (lotto[i] == lotto[j]) { // 중복 검사
                i--;
                break;
            }
        }
    }
}

// 5. 메인 함수
int main() {
    int lotto[SIZE];

    generateLotto(lotto);

    for (int i=0; i<SIZE; i++) {
        printf("%d ", lotto[i]);
    }

    return 0;
}
