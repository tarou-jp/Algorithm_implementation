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

// 選択ソート
void selectionSort(int *array,int size){
    int i;
    int j;
    int tmp;
    int min_index;  // 配列内のi番目に小さい値が格納されたインデックス番号を入れる。
    for (i=0;i<size;i++){
        min_index = i;  // 初期化
        for (j=i;j < size;j++){  // i番目に小さい要素を探すためのfor文であり、繰り返し終了後にはtmp1にi番目に小さい要素が入ったインデックスが代入されている。
            if (array[j] < array[min_index]){
                min_index = j;
            }
        }
        // 配列内のi番目の要素と、配列内でi番目に小さい要素を交換
        tmp = array[min_index];
        array[min_index] = array[i];
        array[i] = tmp;
    }
}


int main() {
    int array[ARRAY_SIZE];
    srand(time(NULL));  // 毎回違う配列を生成するため、シード値を設定

    fillArrayWithRandomNumbers(array, ARRAY_SIZE);  // 配列の初期化

    printf("%s","ソート前:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    selectionSort(array,ARRAY_SIZE);  

    printf("%s","ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}