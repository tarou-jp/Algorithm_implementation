# 最急降下法を行うソースコード

import math

# 最適化問題として解く関数（xのみの場合）
def func(x):
    return 0.00108896*x**2 - 0.29922*x + 15.3791

# 導関数（xのみの場合）
def dfunc(x):
    return 0.00217792*x - 0.29922

# 初期値
x = 100
# 最大反復回数
max_loop = 10000
# 許容誤差
eps = 1e-6
# 一回の更新で進む量を決めるパラメータ
alpha = 1

# 最急降下法
for i in range(max_loop):
    dx = dfunc(x)
    x -= alpha * dx

    # 途中経過の表示
    print(f"{i+1}解目の計算\tx:{x}")

    # 反復の停止判定
    if abs(dx) < eps:
        break

# 結果の出力
print(f"\ndxが{dx}で終了。\nx:{x}")
print(f"x={x},f(x)={func(x)}")