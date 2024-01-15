# シンプソン法を用いて面積を求めるソースコード

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

def simpson_rule(func, a, b, n, xi, fi, m):
    # 区間を2n個のサブインターバルに分割する
    h = (b - a) / (2 * n)
    S = func(a, xi, fi, m) + func(b, xi, fi, m)

    # 奇数項の和
    print("奇数項の和の計算の途中経過")
    for i in range(1, n+1):
        f = func(a + (2*i - 1) * h, xi, fi, m)
        S += 4 * f
        if (i % 1000 == 0):
            print(f"i：{i} S：{abs(S)}")

    # 偶数項の和
    print("偶数項の和の計算の途中経過")
    for i in range(1, n+1):
        f = func(a + 2*i*h, xi, fi, m)
        S += 2 * f
        if (i % 1000 == 0):
            print(f"i：{i} S：{abs(S)}")

    # 最終的な近似値を計算
    S *= h / 3
    return abs(S)

a = 60
b = 210
n = 50

# サンプリング点
xi = [40, 60, 90, 180, 210, 230]  # データ点のx値
fi = [5.2, 0.0, -3.0, -2.2, 0.0, 4.0]  # データ点のy値
m = 6

result = simpson_rule(lagrange, a, b, n, xi, fi, m)
print(f"断面積：{result}")