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

// 挿入ソート
void insertionSort(int *array, int size) {
    int i;
    int j;
    int v;  // i番目に挿入される値が格納される。
    for (i = 1; i < size; i++) {
        v = array[i];  
        j = i - 1;
        // vより大きい要素を一つ後ろに移動して、vを挿入する場所を探す
        while (array[j] > v && j >= 0) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = v; // vを挿入
    }
}

int main() {
    int array[ARRAY_SIZE];
    srand(time(NULL));  //毎回違うを配列を生成するため、シード値を設定

    fillArrayWithRandomNumbers(array, ARRAY_SIZE);  // 配列の初期化

    printf("ソート前:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    insertionSort(array, ARRAY_SIZE); 

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}