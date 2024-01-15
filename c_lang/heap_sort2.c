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


// upheap操作を実行する関数
void upheap(int *array, int i) {
    int parent = (i - 1) / 2; // iの位置にいるノードの親ノードのインデックスを計算している
     // 親ノードが存在し(i > 0)、かつ、親ノードの値が現在のノードの値より小さい間、ループを続ける
    while (i > 0 && array[parent] < array[i]) {
        int temp = array[i];
        array[i] = array[parent];
        array[parent] = temp;  // 現在のノードの値と親ノードの値を交換する
        i = parent;
        parent = (i - 1) / 2;  // 新しい親ノードのインデックスを計算します
    }
}

// 配列をヒープ構造にするためにupheapを使ってヒープを構築する関数
void insert(int *array, int n) {
    for (int i = 1; i < n; i++) {
        upheap(array, i); // upheap関数を呼び出して、インデックスiにある要素を適切な位置に移動させている。
    }
}

//部分配列をヒープの条件を満たすように並び替える関数
void downheap(int *array, int n, int i) {  // nは部分配列の要素数。iは根ノードの値が格納されたインデックス
    int largest = i;  // 親ノードまたは左右の子ノードのいづれかの値が含まれるインデックス(三つのうち、最も数値が大きいものが選ばれる)
    //配列の先頭を根として、左から右へとレベル順（親から子へ）にノードを配置していくと、i番目の要素にあるノードの左右の子ノードは2*i+1(2)の位置にあることに由縁する。
    int left = 2 * i + 1;  // 親ノードの左の子ノードの値が保存されたインデックス
    int right = 2 * i + 2;  // 親ノードの右の子ノードの値が保存されたインデックス

    if (left < n && array[left] > array[largest])  // 左の子ノードの値が根ノードよりも大きい場合、左の子ノードの値が格納されたインデックスをlargestに代入
        largest = left;

    if (right < n && array[right] > array[largest])  // 右の子ノードの値が根ノードよりも大きい場合、右の子ノードの値が格納されたインデックスをlargestに代入
        largest = right;

    if (largest != i) {  //親ノードよりも大きな子ノードが見つかった際に親ノードの値と子ノードの値を入れ替える。
        int swap = array[i];
        array[i] = array[largest];
        array[largest] = swap;

        downheap(array, n, largest);  
    }
}

// ヒープソート関数
void heapSortUsingUpheap(int *array, int n) {
    insert(array, n); // upheapを使用してヒープを構築している。

    for (int i = n - 1; i > 0; i--) {
        int temp = array[0];  // 根ノードと葉ノード(一番右側にあるもの)を交換
        array[0] = array[i];
        array[i] = temp;
        // 交換後の部分配列に対して、downheapを実行
        downheap(array, i, 0);
    }
}

int main() {
    int array[ARRAY_SIZE];
    srand(time(NULL));

    fillArrayWithRandomNumbers(array, ARRAY_SIZE);

    printf("ソート前:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    heapSortUsingUpheap(array, ARRAY_SIZE);

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    return 0;
}

