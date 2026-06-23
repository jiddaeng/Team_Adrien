#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <string.h>

#define SIZE 6
#define SLOT_HEIGHT 5
#define VELOCITY 20

HANDLE hConsole;

// 색 설정 함수
void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

// 1. 로또 번호 생성 (중복 검사)
// 양수혁
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
// 염유찬
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

// 양수혁
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
// 안지호
void slotDrawAndPrint(int lotto[]) {
    int revealed[SIZE] = {0};
    int colors[SIZE];

    // 슬롯 상태 저장
    int slots[SIZE][SLOT_HEIGHT];

    int i, j, row;

    for (i = 0; i < SIZE; i++) {
        while (1) {
            colors[i] = rand() % SIZE + 9;
            int again = 0;
            for (int j = 0; j < i; j++) {
                if (colors[j] == colors[i]) {
                    again = 1;
                    break;
                }
            }
            if (!again)
                break;
        }
    }

    // 초기값 세팅
    for (i = 0; i < SIZE; i++){
        for (row = 0; row < SLOT_HEIGHT; row++) slots[i][row] = 0;
    }    

    // 슬롯 하나씩 멈추기
    for (i = 0; i < SIZE; i++) {

        int center = (lotto[i] + VELOCITY) % 45;
        if (center == 0) center = 45;

        for (j = 0; j < VELOCITY; j++) {

            // 현재 i번째 슬롯만 회전
            for (row = 0; row < SLOT_HEIGHT; row++) {

                slots[i][row] = center + row - 2;

                while (slots[i][row] < 1)
                    slots[i][row] += 45;

                while (slots[i][row] > 45)
                    slots[i][row] -= 45;
            }

            system("cls");

            printf("=== LOTTO SLOT MACHINE ===\n\n");

            // 세로 출력
            for (row = 0; row < SLOT_HEIGHT; row++) {

                for (int col = 0; col <= i; col++) {
                    if (row == 2) {
                        setColor(colors[col]);
                        printf("● %2d ", slots[col][row]);
                        setColor(7);
                    }
                    else {
                        setColor(colors[col]);
                        printf("  %2d ", slots[col][row]);
                        setColor(7);
                    }
                }

                printf("\n");
            }

            printf("\n배출된 공: ");

            for (int k = 0; k < i; k++) {
                setColor(colors[k]);
                printf("%2d ", revealed[k]);
                setColor(7);
            }

            printf("\n");

            center++;

            if (center > 45)
                center = 1;

            Sleep(30);
        }

        revealed[i] = slots[i][2];
    }

    sortNum(revealed, colors);

    system("cls");

    printf("== 최종 당첨 번호 ==\n\n");

    for (i = 0; i < SIZE; i++) {
        setColor(colors[i]);
        printf("● %2d ", revealed[i]);
        setColor(7);
    }

    printf("\n\n");

    for (i = 0; i < SIZE; i++) {
        lotto[i] = revealed[i];
    }
}

// 4. 등수 판별
// 안지호
int getRank(int count) {
    if (count == 6) return 1;
    else if (count == 5) return 2;
    else if (count == 4) return 3;
    else if (count == 3) return 4;
    else return 5;
}

// 염유찬
void showMyNum(int myNum[]) {
    srand(time(NULL));
    printf("== 나의 번호 ==\n\n");
    int color;
    int colorsForSort[] = {7,7,7,7,7,7};
    sortNum(myNum, colorsForSort);
    setColor(color); // 파란색 계열이 1, 3, 9임
    for (int i=0; i<SIZE; i++) {
        color = pow(3, rand() % 3);
        setColor(color);
        printf("● %2d ", myNum[i]);
    }
    setColor(7);
    printf("\n\n");
}

// 5. 메인 함수
int main() {
    int lotto[SIZE];
    int myNum[SIZE];
    int used[SIZE] = {0};
    int matchCount = 0;
    int i, j;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("=== 로또 슬롯 머신 ===\n\n");

    inputMyNumbers(myNum);

    printf("\n엔터를 누르면 추첨 시작...");
    getchar(); getchar();

    generateLotto(lotto);
    slotDrawAndPrint(lotto);
    showMyNum(myNum);

    // 순서 무관 비교
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (myNum[i] == lotto[j] && used[j] == 0) {
                matchCount++;
                used[j] = 1;
                break;
            }
        }
    }

    printf("맞춘 개수: %d\n", matchCount);
    printf("등수: %d등\n", getRank(matchCount));

    return 0;
}