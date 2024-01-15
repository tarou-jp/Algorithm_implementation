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

//部分配列をヒープの条件を満たすように並び替える関数
void heapify(int *array, int n, int i) {  // nは部分配列の要素数。iは根ノードの値が格納されたインデックス
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

        heapify(array, n, largest);  
    }
}

void heapSort(int *array, int n) {
    int i;  //i以降のインデックスには葉ノードが保存される
    for (i = n / 2 - 1; i >= 0; i--)  // ヒープを作成している。(この時、i=n/2-1からスタートしているのは、i以上n-1以下のインデックスには葉ノードの値が含まれていているからである。)
        heapify(array, n, i); 

    for (i = n - 1; i > 0; i--) {  // 現在の根ノード(一番大きな値を持つ)をヒープから取り出し配列内の一番後ろの要素(葉ノード)と入れ替える。
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);  // 今取り除いた元根ノードの要素を除いて、新たにできた大きさn-1の配列を同様にヒープ条件を満たすように値を入れ替える。
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

    heapSort(array, ARRAY_SIZE);

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    return 0;
}

