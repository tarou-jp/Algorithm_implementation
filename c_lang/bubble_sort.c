#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20

// 0以上100以下のランダムな数値を配列に入れる関数
void fillArrayWithRandomNumbers(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 101;  // 0から100までのランダムな数値
    }
}

// バブルソート
void bubbleSort(int *array, int size) {
    int i;
    int j;
    int tmp;
    int swapped;  // 交換が行われたかを記録するフラグ
    for (i = 0; i < size - 1; i++) {
        for (j = i; j < size - i - 1; j++) {  //配列の0からi番目の要素はすでにソート済みになっているため、j=iから始める。
            if (array[j] > array[j + 1]) {
                // 隣接する要素を交換
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (swapped == 0){  // もし交換が一度も行われなければすでにソート済みであるのでfor文を抜ける
            break;
        }
    }
}

int main() {
    int array[ARRAY_SIZE];
    srand(time(NULL));  // 毎回違う配列を生成するため、シード値を設定

    fillArrayWithRandomNumbers(array, ARRAY_SIZE);  // 配列の初期化

    printf("ソート前:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    bubbleSort(array, ARRAY_SIZE);  

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}