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

// 配列を分割する関数
int partition(int *array, int low, int high) {
    int pivot = array[high];  // ピポットは配列の最後の要素とする。
    int i = (low - 1);  
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {  //ピボットより小さい値が見つかれば、i番目の要素と入れ替える。(ピボット以下の要素が左側に移動されていく。)
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    //現在、low以上i以下のインデックスにはピボット以下の要素がのみ含まれる。そこで、i+1番目の要素とピポットを入れ替えることでピボットを以下の要素とピボット以上の要素で配列内要素を分離できる。
    int temp = array[i + 1];  
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);  //返り値はピボットのインデックス
}

// クイックソート
void quickSort(int *array, int low, int high) {  // lowは現在処理している部分配列の最小インデックスであり、highは最大インデックスである。
    int pi; 
    if (low < high) {  // 以下を処理する部分配列の大きさが0になるまで繰り返す。
        pi = partition(array, low, high);  // partition関数によってピポットの正しい位置のインデックスを取得する。
        quickSort(array, low, pi - 1);  // ピポットよりも左側を新たな部分配列にして再帰的にquickSortを呼び出す。
        quickSort(array, pi + 1, high);    // ピポットよりも右側を新たな部分配列にして再帰的にquickSortを呼び出す。
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

    quickSort(array, 0, ARRAY_SIZE - 1);

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}