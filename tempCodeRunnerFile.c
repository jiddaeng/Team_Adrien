unt == 4) return 3;
    else if (count == 3) return 4;
    else return 5;
}

void showMyNum(int myNum[]) {
    srand(time(NULL));
    printf("== 나의 번호 ==\n\n");
    int color;
    int colorsForSort[] = {7,7,7,7,7,7};