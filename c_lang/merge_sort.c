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

// マージ関数
void merge(int *array, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;  // 分割されたソート済みの部分配列のうち、左側の要素数
    int n2 = right - middle;  // 分割されたソート済みの部分配列のうち、右側の要素数

    // 一時配列を作成
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // ソート済みの部分配列をそれぞれL,Rにコピーしている。
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    // 一時配列から配列にマージしながらソート
    i = 0;  // 左の部分配列のための初期インデックス
    j = 0;  // 右の部分配列のための初期インデックス
    k = left;  // マージされた部分配列の初期インデックス
    
    while (i < n1 && j < n2) {  //二つの部分配列から小さい順に値を取り出し一つの配列に結合している。
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Lの残りをコピー
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Rの残りをコピー
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    // 動的に割り当てたメモリを解放
    free(L);
    free(R);
}

// マージソート関数
void mergeSort(int *array, int left, int right) {  // leftは現在処理している部分配列の最小インデックスであり、rightは最大インデックスである。
    if (left < right) { // 以下を処理する部分配列の大きさが0になるまで繰り返す。
        int middle = left + (right - left) / 2;// 同じくらいのサイズの二つの部分配列に分割する中間点のインデックス

        mergeSort(array, left, middle);  // middleよりも左側を新たな部分配列にして再帰的にmargeSortを呼び出す。
        mergeSort(array, middle + 1, right);  // middleよりも右側を新たな部分配列にして再帰的にmargeSortを呼び出す。

        merge(array, left, middle, right);  //ソートされた部分配列を一つの配列にソートしながら組み合わせる。(再帰的に一番深い場所では要素数が1の部分配列であるからソート済みの部分配列となる)
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

    // マージソート関数を呼び出し
    mergeSort(array, 0, ARRAY_SIZE - 1);

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}