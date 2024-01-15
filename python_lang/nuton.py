# ニュートン法を行うソースコード

import random

# 球根問題として解く関数
def func(x):
    return x**2-2374
#導関数
def dfunc(x):
    return 2*x

#xの初期値
x = 48
#最大反復回数
max_loop = 100
# 許容誤差
eps = 1e-6

#ニュートン法
for i in range(max_loop):
    f = func(x)
    df = dfunc(x)
    
    # 導関数を用いて、xを更新
    if (df != 0):
        x = x - f/df
    else:
        # 導関数が0に近い場合、xに小さな乱数を加える
        x += random.uniform(-1e-4, 1e-4)
        continue

    #途中経過の表示
    print(f"{i+1}解目の計算です。\nx:{x}")

    # 反復の停止判定に使用する変数
    dx_abs = f/df if f/df >= 0 else -f/df
    df_abs = df if df >= 0 else -df
    
    # 反復の停止判定
    if (dx_abs < eps or df_abs < eps):
        break

# 結果の出力
print(f"\ndxが{dx_abs}で終了。\nx:{x}\nx^2={x**2}")