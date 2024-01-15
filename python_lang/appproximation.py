# 与えられた離散点から最小２乗法を用いて関数回帰を行い、求めた関数に対して再急降下法を用いて最小点を求めるソースコード

import numpy as np
import cholesky
import matplotlib.pyplot as plt

def plot_approximation_with_min_point(xi, fi, c, n, min_x):
    # xの値の範囲を決定（データポイントの最小値と最大値に基づく）
    x_min, x_max = min(xi), max(xi)
    x_values = np.linspace(x_min, x_max, 500)  # グラフに表示するためのx値のリスト

    # 近似関数 f(x) の値を計算
    y_values = [func(c, x) for x in x_values]

    # データポイントと近似曲線をプロット
    plt.scatter(xi, fi, color='red', label='Data points')  # データポイント
    plt.plot(x_values, y_values, label='Approximation')     # 近似曲線

    # 最小値を与える点をプロット
    min_y = func(c, min_x)
    plt.scatter(min_x, min_y, color='blue', marker='*', s=100, label='Minimum point')

    # グラフの設定
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Polynomial Approximation with Minimum Point')
    plt.legend()

    # グラフの表示
    plt.show()


def func(c,x):
    return c[0][0] + c[1][0]*x + c[2][0]*x**2

def dfunc(c,x):
    return c[1][0] + 2*c[2][0]*x

def build_least_squares_matrix(xi, fi, n):
    m = len(xi)
    dim_b = n + 1

    # 係数行列 A と右辺項 y の初期化
    A = np.zeros((dim_b, dim_b))
    y = np.zeros((dim_b,1))

    # 係数行列と右辺項の構築
    for k in range(m):
        xb = 1
        for i in range(dim_b):
            for j in range(dim_b):
                A[i, j] += xb * xi[k]**j
            y[i][0] += xb * fi[k]
            xb *= xi[k]

    X = np.zeros((dim_b,1))
    C = cholesky.cholesky(A,X,y)
    
    # 結果の表示
    print(f"c={[X[i][0] for i in range(dim_b)]}")
        
    # 初期値
    x = 100
    # 最大反復回数
    max_loop = 10000
    # 許容誤差
    eps = 1e-6
    # 一回の更新で進む量を決めるパラメータ
    alpha = 100

    # 最急降下法
    for i in range(max_loop):
        dx = dfunc(C,x)
        x -= alpha * dx

        # 途中経過の表示
        print(f"{i+1}回目の計算\tx:{x}")

        # 反復の停止判定
        if abs(dx) < eps:
            break

    plot_approximation_with_min_point(xi, fi, C, n, x)

    # 結果の出力
    print(f"\ndxが{dx}で終了。\nx:{x}")
    print(f"x={x},f(x)={func(C,x)}")

# 例としての使用
xi = [40, 60, 90, 180, 210, 230]  # データ点の x 値
fi = [5.3, 0.0, -3.0, -2.2, 0.0, 4.0]  # データ点の y 値
n = 2  # 多項式の次数

build_least_squares_matrix(xi, fi, n)