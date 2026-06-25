#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define SIZE 6
#define SLOT_HEIGHT 5
#define VELOCITY 20

HANDLE hConsole;

// 색 설정 함수
void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

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

// 3. 슬롯머신 멋있는 연출
void slotDrawAndPrint(int lotto[]) {
    int revealed[SIZE] = {0};
    int colors[SIZE];
    int i, j, k, temp;

    for (i = 0; i < SIZE; i++) {
        colors[i] = rand() % 6 + 9; // 밝은 색
    }

    for (i = 0; i < SIZE; i++) { // i는 로또 추첨 개수
        int temp = lotto[i]+VELOCITY*1 % 45;
        for (j = 0; j < VELOCITY; j++) { // j는 그냥 연출용
            system("cls");
            printf("=== LOTTO SLOT MACHINE ===\n\n");

            // 슬롯 세로 출력
            for (k = 0; k < SLOT_HEIGHT; k++) {
                if (k == SLOT_HEIGHT - 3) {
                    setColor(colors[i]);
                    printf("   ● %2d\n", temp+k);
                    setColor(7);
                } else {
                    printf("   | %2d\n", temp+k);
                }
            }
            temp += 1;
            if (temp+3 > 45) temp = 1;

            // 이미 나온 공
            printf("\n배출된 공: ");
            for (k = 0; k < i; k++) {
                setColor(colors[k]);
                printf("%2d ", revealed[k]);
                setColor(7);
            }

            Sleep(10);
        }

        revealed[i] = lotto[i];
    }

    // 정렬
    sortNum(revealed, colors);

    // 최종 출력
    system("cls");
    printf("== 최종 당첨 번호 ==\n\n");
    for (i = 0; i < SIZE; i++) {
        setColor(colors[i]);
        printf("● %2d  ", revealed[i]);
        setColor(7); // 기본 색, 회색
    }
    printf("\n\n");

    for (i = 0; i < SIZE; i++) {
        lotto[i] = revealed[i];
    }
}

// 5. 메인 함수
int main() {
    int lotto[SIZE];
    int myNum[SIZE];
    int matchCount = 0;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("=== 로또 슬롯 머신 ===\n\n");

    inputMyNumbers(myNum);

    printf("\n엔터를 누르면 추첨 시작...");
    getchar(); getchar();

    generateLotto(lotto);
    slotDrawAndPrint(lotto);

    return 0;
}
