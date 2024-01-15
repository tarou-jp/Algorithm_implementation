# 与えられた離散点からラグランジュ法による関数補完を行い、補完点を黄金分割法の分割点として利用し、最小値を求めるソースコード

import numpy as np
import matplotlib.pyplot as plt
import math

# ラグランジュ補完
def lagrange(x,xi,fi,n):
    Ln = 0
    for i in range(n):
        l = 1
        for j in range(n):
            if (j == i):
                continue
            l *= (x - xi[j])/(xi[i]-xi[j])
        Ln += fi[i]*l
    return Ln

def golden_section_method(xl,xr,xi,fi,n):
    max_loop = 10000
    eps = 1e-6
    e = (math.sqrt(5)-1.0)/(math.sqrt(5)+1.0)
    b = xr-xl
    d = e*b

    x = [xl,xl+d,xr-d,xr]

    f1 = lagrange(x[1],xi,fi,n)
    f2 = lagrange(x[2],xi,fi,n)

    for k in range(max_loop):
        if (f1 < f2):
            x2 = x[2]
            x[2] = x[1]
            x[1] = x2 - d
            x[3] = x2
            f2 = f1
            f1 = lagrange(x[1],xi,fi,n)
        else:
            x1 = x[1]
            x[1] = x[2]
            x[2] = x1 + d
            x[0] = x1
            f1 = f2
            f2 = lagrange(x[2],xi,fi,n)
        b -= d
        d = e*b

        print(f"反復回数:{k} x[0]:{x[0]}")

        if (b < eps):
            print(f"誤差(分割点x[1]とx[2]の距離){b}")
            break
    
    return x


def figure_create(xi_,fi_,n_,min_x,min_y):
    x_plot = []
    y_plot = []

    for i in range(40,231,1):
        x_plot.append(i)
        y_plot.append(lagrange(i,xi_,fi_,n_))

    # 元のサンプル点と補間された曲線をプロット
    plt.figure(figsize=(10, 6))
    plt.plot(xi, fi, 'o', label='sample point')
    plt.plot(x_plot, y_plot, '-', label='lagrange')
    plt.scatter(min_x, min_y, color='blue', marker='*', s=100, label='Minimum point')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid(True)
    plt.show()

# サンプリング点
xi = np.array([40, 60, 90, 180, 210, 230])  # データ点のx値
fi = np.array([5.2, 0.0, -3.0, -2.2, 0.0, 4.0])  # データ点のy値
n = 6

x = golden_section_method(xi[0],xi[-1],xi,fi,n)
y = lagrange(x[0],xi,fi,n)
figure_create(xi,fi,n,x[0],y)

print(f"x：{x[0]} 最大水深：{y}")

