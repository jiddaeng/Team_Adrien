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

// 2. 내 번호 입력 (범위 + 중복 검사)
void inputMyNumbers(int myNum[]) {
    int i, j, num;

    printf("내 번호 6개 입력 (1~45)\n");

    for (i = 0; i < SIZE; i++) {
        while (1) {
            scanf("%d", &num);

            if (num < 1 || num > 45) {
                printf("범위 오류! 다시 입력: ");
                continue;
            }

            for (j = 0; j < i; j++) {
                if (myNum[j] == num) {
                    printf("중복 숫자! 다시 입력: ");
                    break;
                }
            }

            if (j == i) {
                myNum[i] = num;
                break;
            }
        }
    }
}

// colors는 이후 로또 연출을 위해
void sortNum(int revealed[], int colors[]) {
    int temp;

    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {

            if (revealed[j] > revealed[j + 1]) {

                temp = revealed[j];
                revealed[j] = revealed[j + 1];
                revealed[j + 1] = temp;

                temp = colors[j];
                colors[j] = colors[j + 1];
                colors[j + 1] = temp;
            }
        }
    }
}

// 5. 메인 함수
int main() {
    int lotto[SIZE];
    int myNum[SIZE];
    int colors[SIZE] = {7,7,7,7,7,7}; // 7이 기본값, 회색

    inputMyNumbers(myNum);
    generateLotto(lotto);

    printf("내 번호: ");
    for (int i=0; i<SIZE; i++) {
        printf("%d ", myNum[i]);
    }
    printf("\n");
    printf("로또 번호: ");
    for (int i=0; i<SIZE; i++) {
        printf("%d ", lotto[i]);
    }
    printf("\n");
    sortNum(lotto, colors);
    printf("정렬 후: ");
    for (int i=0; i<SIZE; i++) {
        printf("%d ", lotto[i]);
    }

    return 0;
}
