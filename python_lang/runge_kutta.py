# ばねに吊り下げられた物体の運動をグラフ化するソースコード

import numpy as np
import matplotlib.pyplot as plt

def plot_y_vs_t(t0, t_end, n, y_list):
    # 時間のデータポイントを生成
    t_values = np.linspace(t0, t_end, n+1)

    # プロット
    plt.figure(figsize=(10, 6))
    plt.plot(t_values, y_list, label='y(t)', color='blue')
    
    # タイトルと軸ラベルを設定
    plt.xlabel('time[t]')
    plt.ylabel('y[m]')

    # 凡例の表示
    plt.legend()

    # グリッドを表示
    plt.grid(True)

    # グラフを表示
    plt.show()

# 微分方程式の右辺を定義
def ddfunc(y, v):
    # パラメータ設定
    m = 1.0  # 質量
    k = 0.851  # ばね定数
    c = 0.1  # 減衰係数
    g = 9.8  # 重力加速度
    a = (-k * y - 2 * c * v + m * g) / m
    return a


# ルンゲ・クッタ法の関数
def runge_kutta_4th(t0, y0, v0, t_end, n):
    y_list = []
    h = (t_end - t0) / n
    t = t0
    v = v0
    y = y0
    y_list.append(y)
    
    for i in range(n):
        k1 = h * v
        l1 = h * ddfunc(y, v)

        k2 = h * (v + l1/2)
        l2 = h * ddfunc(y + k1/2, v + l1/2)
        
        k3 = h * (v + l2/2)
        l3 = h * ddfunc(y + k2/2, v + l2/2)

        k4 = h * (v + l3)
        l4 = h * ddfunc(y + k3, v + l3)

        y += (k1 + 2*k2 + 2*k3 + k4) / 6
        v += (l1 + 2*l2 + 2*l3 + l4) / 6
        t += h

        y_list.append(y)
        if abs(t % 5) < 0.005: #丸め誤差のためt==10.0では機能しないため、このようにしています。
            print(f"t: {int(t)} y:{y}")
        
    return y_list

# 初期条件
t0 = 0.0
y0 = 0.0
v0 = 0.0
t_end = 50.0
n = 1000

# ルンゲ・クッタ法を実行
y_list = runge_kutta_4th(t0,y0,v0,t_end,n)
plot_y_vs_t(t0, t_end, n, y_list)