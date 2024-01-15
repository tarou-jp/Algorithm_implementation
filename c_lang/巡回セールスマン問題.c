#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define MAX_NODES 10 //最大ノード数を10としておく。

typedef struct
{
    int NodeNum1;
    int NodeNum2;
    float Weight;
    int Join; //使用できる道の数を表す。join=0であれば、その道は使用できず、join=n(n!=0)であればその道をn回使用できる。
} Edge;

typedef struct
{
    int NodeNum;
    int Parent;
} Node;

//ノードの祖先ノードを探す関数。(kruskal法において、閉路をエッジの追加により閉路が作成されないかを調べるために使用する。)
int GetParent(int num, Node nodes[], int n)
{
    int parent = nodes[num].Parent;
    while (parent != -1 && parent != nodes[parent].Parent) //条件式より、根ノードに到達するまで親ノードへ遡る。
    {
        parent = nodes[parent].Parent;
    }
    return parent; 
}

//エッジ配列をエッジの重さ(道の長さ)の降順でソートする関数。(kruskal法において使用する)
void bubbleSortEdges(Edge edges[], int numberOfEdges)
{
    int i, j;
    for (i = 0; i < numberOfEdges - 1; i++)
    {
        for (j = 0; j < numberOfEdges - i - 1; j++)
        {
            if (edges[j].Weight > edges[j + 1].Weight)
            {
                // エッジを交換する
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal(Node nodes[], Edge edges[], int n, int e)
{
    //エッジのソート
    bubbleSortEdges(edges, e);

    //エッジを重さが小さいものから順に閉路を作らないように追加して、最小全域木を作成
    for (int i = 0; i < e; i++)
    {
        //エッジのつながっているノード
        int num1 = edges[i].NodeNum1; 
        int num2 = edges[i].NodeNum2;

        //エッジのつながっているノードの祖先ノード
        int parentNum1 = GetParent(num1, nodes, n);
        int parentNum2 = GetParent(num2, nodes, n);
        
        //祖先ノードが-1であれば、そのノードはまだ作成途中の最小全域木に含まれていない。
        if (parentNum1 == -1 || parentNum2 == -1)
        {
            //祖先ノードが-1のノードを取得。エッジの両端のノードがどちらも祖先ノードが-1であれば、数字が若い方を選択
            int parentNum = (parentNum1 != -1) ? parentNum1 : parentNum2;
            if (parentNum == -1)
            {
                parentNum = (num1 < num2) ? num1 : num2;
            }
        
            //祖先ノードが-1であるノードが親ノードになるように２つのノードを結合
            nodes[num1].Parent = parentNum;
            nodes[num2].Parent = parentNum;
            edges[i].Join = 1; 
        }
        //エッジ両端のノードがすでに木に含まれている時
        else
        {
            //祖先ノードが同じであれば、そのエッジをつなげることにより閉路が作成されるためエッジを追加しない。
            if (parentNum1 != parentNum2)
            {
                //エッジを追加してエッジ両端のノードを結合
                edges[i].Join = 1;
                int numTo = (parentNum1 < parentNum2) ? parentNum1 : parentNum2;
                int numFrom = (parentNum1 > parentNum2) ? parentNum1 : parentNum2;
                nodes[numFrom].Parent = numTo;
            }
        }
    }

    //最小全域木に含まれるエッジの重さの合計を表示
    float totalWeight = 0.0f;
    printf("最小全域木に含まれる道:\n");
    for (int i = 0; i < e; i++)
    {
        if (edges[i].Join)
        {
            totalWeight += edges[i].Weight;
            printf("(%d, %d) - Weight: %.4f\n", edges[i].NodeNum1+1, edges[i].NodeNum2+1, edges[i].Weight);//ノード番号を1から開始するために+1している
        }
    }
    printf("最小全域木を構成する道の総重量: %.4f\n", totalWeight);
}

// 最小全域木から次数(そのノードに接続されているエッジの数)が偶数のノードを探す関数
void findOddDegreeNodes(Edge edges[], int n, int e, int oddNodes[], int *oddCount)
{
    *oddCount = 0;
    int *degree = (int *)malloc(n * sizeof(int));
    //ノードの次数が格納される配列を0で初期化(使い方として、例えばdegree=[2,2,3]の場合、ノード0とノード1の次数が2、ノード2の次数が3となる)
    for (int i = 0; i < n; i++)
    {
        degree[i] = 0; 
    }

    //最小全域木に含まれるエッジを使って各ノードの次数を計算
    for (int j = 0; j < e; j++)
    {
        if (edges[j].Join)
        { //このエッジが最小全域木に含まれるかチェックし、含まれる場合はdegreeに記録
            degree[edges[j].NodeNum1]++;
            degree[edges[j].NodeNum2]++;
        }
    }

    // 配列degreeにより奇数次数のノードを探す。
    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 != 0)
        {
            oddNodes[(*oddCount)++] = i;
        }
    }

    free(degree);
}

//２つのノード間にエッジが存在するかどうかをチェックする関数
int edgeExists(int nodeIndex1, int nodeIndex2, Edge edges[], int edgeCount)
{
    for (int i = 0; i < edgeCount; i++)
    {
        if ((edges[i].NodeNum1 == nodeIndex1 && edges[i].NodeNum2 == nodeIndex2) ||
            (edges[i].NodeNum2 == nodeIndex1 && edges[i].NodeNum1 == nodeIndex2))
        {
            return 1; // エッジが存在する
        }
    }
    return 0; // エッジが存在しない
}

//次数が奇数のノードの重みが最小になる完全マッチングを見つけるための関数
//この関数は、考えられるすべての完全マッチングを作成して重みを計算しているため、ノード数が増えると計算量が増えてしまう。
void pairNodes(int level, int nodeCount, Edge edges[], int edgeCount, int currentMatching[], int used[], float *minWeight, int minMatching[], int nodes[])
{
    // すべてのノードがペアリングされた場合
    if (level == nodeCount)
    {
        float currentWeight = 0;
        // 現在のペアリングの重みを計算
        for (int i = 0; i < nodeCount; i += 2)
        {
            if (edgeExists(currentMatching[i], currentMatching[i + 1], edges, edgeCount))
            {
                for (int j = 0; j < edgeCount; j++)
                {
                    // エッジが存在する場合のみ重みを加算
                    if ((edges[j].NodeNum1 == currentMatching[i] && edges[j].NodeNum2 == currentMatching[i + 1]) ||
                        (edges[j].NodeNum2 == currentMatching[i] && edges[j].NodeNum1 == currentMatching[i + 1]))
                    {
                        currentWeight += edges[j].Weight;
                        break; // 重みを見つけたらその他のエッジは見ない
                    }
                }
            }
            else
            {
                currentWeight = FLT_MAX; // 存在しないエッジの場合は無効な重みとする
                break;
            }
        }

        // 現在の重みが最小重みより小さければ更新
        if (currentWeight < *minWeight)
        {
            // 有効な重みの場合のみ出力
            if (currentWeight < FLT_MAX)
            {
                // currentMatchingを出力
                printf("Current Matching: ");
                for (int i = 0; i < nodeCount; i += 2)
                {
                    printf("(%d, %d) ", currentMatching[i], currentMatching[i + 1]);
                }
                printf("Current Weight: %f\n", currentWeight);
            }
            *minWeight = currentWeight;
            // 最小マッチングを更新
            for (int i = 0; i < nodeCount; i++)
            {
                minMatching[i] = currentMatching[i];
            }
        }
    }
    else
    {
        // 再帰的にすべてのペアリングを試す
        for (int i = 0; i < nodeCount; i++)
        {
            if (!used[i])
            {
                used[i] = 1;
                currentMatching[level] = nodes[i];
                pairNodes(level + 1, nodeCount, edges, edgeCount, currentMatching, used, minWeight, minMatching, nodes);
                used[i] = 0; // バックトラック
            }
        }
    }
}

//最小全域木において次数が奇数になるノード同士の重みが最小となる完全マッチングを探す関数
void findMinWeightCompleteMatching(int nodes[], int nodeCount, Edge edges[], int edgeCount)
{
    float minWeight = FLT_MAX;
    int minMatching[MAX_NODES];
    //currentMatchingでは、インデックスが偶数の時、そのノードのペアとして右隣のインデックスに保存された値のノードを持つ。
    int currentMatching[MAX_NODES];
    //そのノードがcurrentMatchingに含まれることを表す。(1であればcurrentMatchingにそのノードが含まれることを表す。)
    int used[MAX_NODES] = {0};

    // 配列の初期化
    for (int i = 0; i < MAX_NODES; i++)
    {
        currentMatching[i] = -1; 
        used[i] = 0;
    }

    //全パターンの完全マッチングを模索して重みが最小のマッチングを見つける。
    pairNodes(0, nodeCount, edges, edgeCount, currentMatching, used, &minWeight, minMatching, nodes);

    //完全マッチングに使用されたエッジのjoinを1引き上げる。これにより、ノードをjoinが0でないエッジで結べばオイラーグラフになっている。
    for (int i = 0; i < nodeCount; i += 2)
    {
        if (minMatching[i] != -1 && minMatching[i + 1] != -1)
        {

            for (int j = 0; j < edgeCount; j++)
            {
                if ((edges[j].NodeNum1 == minMatching[i] && edges[j].NodeNum2 == minMatching[i + 1]) ||
                    (edges[j].NodeNum2 == minMatching[i] && edges[j].NodeNum1 == minMatching[i + 1]))
                {
                    edges[j].Join += 1;
                    break;
                }
            }
        }
    }

    //完全マッチングを生成するエッジの重みの合計を表示 
    printf("Minimam weight complete matching: %.4f\n\n", minWeight);
}

//オイラーグラフから、すべてのノードを通りもとのノードに帰ってくる経路(オイラー回路)を作成。(同じノードに複数回訪れることを許可して経路を作成)
void findEulerianCircuit(Edge edges[], int edgeCount, int currentNode, int path[], int *pathIndex)
{
    for (int i = 0; i < edgeCount; i++)
    {
        if (edges[i].Join > 0 && (edges[i].NodeNum1 == currentNode || edges[i].NodeNum2 == currentNode))
        {
            edges[i].Join--; // エッジを訪問済みにする
            int nextNode = (edges[i].NodeNum1 == currentNode) ? edges[i].NodeNum2 : edges[i].NodeNum1;
            findEulerianCircuit(edges, edgeCount, nextNode, path, pathIndex);
        }
    }
    path[(*pathIndex)++] = currentNode; 
}

// オイラー回路からハミルトン回路を作成する関数
void createHamiltonianCircuit(int eulerCircuit[], int circuitSize, int hamiltonCircuit[], int *hamiltonSize, int visited[])
{
    //オイラー回路をたどり、すでに訪問済みのノードに訪れた際にはそのノードを無視することでハミルトン回路を作成。つまり、オイラー回路が1→2→3→2→1のような場合、二度目の訪問となる2を無視して1→2→3→1というハミルトン回路を作成する。
    *hamiltonSize = 0;
    for (int i = 0; i < circuitSize; i++)
    {
        if (!visited[eulerCircuit[i]])
        {
            visited[eulerCircuit[i]] = 1;
            hamiltonCircuit[(*hamiltonSize)++] = eulerCircuit[i];
        }
    }
    hamiltonCircuit[(*hamiltonSize)++] = eulerCircuit[0];
}

int main()
{
    int n = 8;
    Node *nodes = (Node *)malloc(n * sizeof(Node));
    //ノードの初期化
    for (int i = 0; i < n; i++)
    {
        nodes[i].NodeNum = i;
        nodes[i].Parent = -1;
    }

    //エッジの初期化(ノード番号が0から振り分けられるようにしている)
    Edge edges[] = {
        {0, 1, 1.7321}, {0, 2, 1.0}, {0, 3, 1.0}, {0, 4, 1.7321}, {1, 2, 1.0}, {1, 4, 1.7321}, {1, 5, 1.0}, {2, 3, 1.7321}, {2, 5, 1.7321}, {3, 4, 1.0}, {3, 5, 1.7321}, {4, 5, 1.0}};
    int e = sizeof(edges) / sizeof(edges[0]);
 
    //最小全域木を作成
    kruskal(nodes, edges, n, e);
    printf("\n");

    int *oddNodes = (int *)malloc(n * sizeof(int));
    int oddCount;
    //最小全域木から次数が奇数のノードを抽出
    findOddDegreeNodes(edges, n, e, oddNodes, &oddCount);
    printf("次数が奇数のノード:\n");
    for (int i = 0; i < oddCount; i++)
    {
        printf("Node %d\n", oddNodes[i]+1);//ノード番号を1から開始するために+1している
    }
    printf("\n");

    //次数が奇数のノード同士で重みが最小となる完全マッチングを作成
    findMinWeightCompleteMatching(oddNodes, oddCount, edges, e);

    int *eulerCircuit = (int *)malloc(MAX_NODES * sizeof(int));
    int circuitIndex = 0;
    //最小全域木で使用するエッジと完全マッチングで使用するエッジを合わせてオイラー回路を作成
    findEulerianCircuit(edges, e, 0, eulerCircuit, &circuitIndex);

    int *hamiltonCircuit = (int *)malloc(n * sizeof(int));
    int hamiltonSize = 0;
    int *visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    //オイラー回路からハミルトン回路を作成
    createHamiltonianCircuit(eulerCircuit, circuitIndex, hamiltonCircuit, &hamiltonSize, visited);

    //ノード番号を1から開始するために+1している
    printf("解: ");
    for (int i = 0; i < hamiltonSize-1; i++)
    {
        printf("%d → ", hamiltonCircuit[i]+1);
    }
    printf("%d \n",hamiltonCircuit[0]+1);

    //算出された経路の重さの総量を表示
    float weight_result = 0;
    for (int i = 0; i < hamiltonSize - 1; i++)
    {
        for (int j = 0; j < e; j++)
        {
            if ((edges[j].NodeNum1 == hamiltonCircuit[i] && edges[j].NodeNum2 == hamiltonCircuit[i + 1]) || (edges[j].NodeNum2 == hamiltonCircuit[i] && edges[j].NodeNum1 == hamiltonCircuit[i + 1]))
            {
                weight_result += edges[j].Weight;
                break;
            }
        }
    }
    printf("重さ：%f \n", weight_result);


    free(oddNodes);
    free(eulerCircuit);
    free(hamiltonCircuit);
    free(visited);
    free(nodes);
    return 0;
}
