#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

// 1. 번호 생성 함수 (중복 검사 포함)
void generateNumbers(int lotto[]) {
    int i, j;
    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        lotto[i] = rand() % 45 + 1;

        // 중복 검사
        for (j = 0; j < i; j++) {
            if (lotto[i] == lotto[j]) {
                i--; // 중복이면 다시 생성
                break;
            }
        }
    }
}

// 2. 오름차순 정렬 함수
void sortNumbers(int lotto[]) {
    int i, j, temp;

    for (i = 0; i < SIZE - 1; i++) {
        for (j = i + 1; j < SIZE; j++) {
            if (lotto[i] > lotto[j]) {
                temp = lotto[i];
                lotto[i] = lotto[j];
                lotto[j] = temp;
            }
        }
    }
}

// 3. 출력 함수
void printNumbers(int lotto[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", lotto[i]);
    }
    printf("\n");
}

// 4. 등수 제공 함수
int getRank(int matchCount) {
    if (matchCount == 6) return 1;
    else if (matchCount == 5) return 2;
    else if (matchCount == 4) return 3;
    else if (matchCount == 3) return 4;
    else return 5;
}

// 5. 메인 함수
int main() {
    int lotto[SIZE];
    int myNum[SIZE];
    int i, j;
    int matchCount = 0;

    printf("=== 로또 번호 생성기 ===\n");

    // 번호 생성
    generateNumbers(lotto);
    sortNumbers(lotto);

    // 내 번호 입력
    printf("내 번호 6개를 입력하세요:\n");
    for (i = 0; i < SIZE; i++) {
        scanf("%d", &myNum[i]);
    }

    // 맞춘 개수 계산
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (myNum[i] == lotto[j]) {
                matchCount++;
            }
        }
    }

    // 결과 출력
    printf("\n생성된 로또 번호: ");
    printNumbers(lotto);

    printf("맞춘 개수: %d\n", matchCount);
    printf("등수: %d등\n", getRank(matchCount));

    return 0;
}