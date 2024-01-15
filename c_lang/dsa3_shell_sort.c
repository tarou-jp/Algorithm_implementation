// #include <stdio.h>
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
void insertionSort(int a[], int N, int l,int k) {
    int i;
    int j;
    int v;  // i番目に挿入される値が格納される。
    for (i = l; i < N; i = i+k) {
        v = a[i];  
        j = i - 1;
        // vより大きい要素を一つ後ろに移動して、vを挿入する場所を探す
        while (a[j] > v && j >= 0) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = v; // vを挿入
    }
}


void shell_sort( int a[], int N ){
    int k;
    int l;

    for (k=5;k>=1;k--){
        for (l=0;l+k<=N;l++){
            printf("h=%d    l=%d\n",k,l);
            insertionSort(a,N,l,k);
        }
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

    shell_sort(array, ARRAY_SIZE); 

    printf("ソート後:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}