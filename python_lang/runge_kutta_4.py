# ばねに吊り下げられた2物体の運動をグラフ化するソースコード

import numpy as np
import matplotlib.pyplot as plt

# パラメータ設定
m = 1.0  # 質量
k = 0.851  # ばね定数
c = 0.1  # 減衰係数
g = 9.8  # 重力加速度

def plot_y1_y2_vs_t(t0, t_end, n, y1_list, y2_list):
    # 時間のデータポイントを生成
    t_values = np.linspace(t0, t_end, n+1)

    # プロット
    plt.figure(figsize=(10, 6))
    plt.plot(t_values, y1_list, label='y1(t)', color='blue')
    plt.plot(t_values, y2_list, label='y2(t)', color='green')
    
    # タイトルと軸ラベルを設定
    plt.xlabel('Time[t]')
    plt.ylabel('y1[m] and y2[m]')

    # 凡例の表示
    plt.legend()

    # グリッドを表示
    plt.grid(True)

    # グラフを表示
    plt.show()

# 物体1の2階微分方程式
def ddfunc1(y, v):
    a = (-k * y - 2 * c * v + m * g) / m
    return a

# 物体2の2階微分方程式
def ddfunc2(y1 ,y2 , v):
    a = (-k * (y2 - y1) - 2*c * v + m * g) / m
    return a

# ルンゲ・クッタ法の関数
def runge_kutta_4th(t0, y1_0, y2_0, v1_0, v2_0, t_end, n):
    y1_list = []
    y2_list = []
    h = (t_end - t0) / n
    t = t0
    v1 = v1_0
    v2 = v2_0
    y1 = y1_0
    y2 = y2_0
    y1_list.append(y1)
    y2_list.append(y2)
    
    for i in range(n): 
        k1 = h * v1 #y1用
        l1 = h * v2 #y2用
        m1 = h * ddfunc1(y1,v1) #v1用
        n1 = h * ddfunc2(y1, y2, v2) #v2用

        k2 = h * (v1 + m1/2)
        l2 = h * (v2 + n1/2)
        m2 = h * ddfunc1(y1 + k1/2,v1 + m1/2)
        n2 = h * ddfunc2(y1 + k1/2, y2 + l1/2, v2 + n1/2)

        k3 = h * (v1 + m2/2)
        l3 = h * (v2 + n2/2)
        m3 = h * ddfunc1(y1 + k2/2,v1 + m2/2)
        n3 = h * ddfunc2(y1 + k2/2, y2 + l2/2, v2 + n2/2)

        k4 = h * (v1 + m3)
        l4 = h * (v2 + n3)
        m4 = h * ddfunc1(y1 + k3, v1 + m3)
        n4 = h * ddfunc2(y1 + k3, y2 + l3 ,v2 + n3)
   
        y1 += (k1 + 2*k2 + 2*k3 + k4) / 6
        y2 += (l1 + 2*l2 + 2*l3 + l4) / 6
        v1 += (m1 + 2*m2 + 2*m3 + m4) / 6
        v2 += (n1 + 2*n2 + 2*n3 + n4) / 6
        t += h
        if abs(t % 5) < 0.005: #丸め誤差のためt==10.0では機能しないため、このようにしています。
            print(f"t: {int(t)} y1:{y1} y2:{y2}")

        y1_list.append(y1)
        y2_list.append(y2)

    return y1_list,y2_list



# 初期条件
t0 = 0.0
y1_0 = 0.0
y2_0 = 5.0
v0 = 0.0
t_end = 50.0
n = 10000

# ルンゲ・クッタ法を実行
y1_list,y2_list = runge_kutta_4th(t0,y1_0,y2_0,v0,v0,t_end,n)
plot_y1_y2_vs_t(t0, t_end, n, y1_list,y2_list)