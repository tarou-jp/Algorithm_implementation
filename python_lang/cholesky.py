# 修正コレスキー分解を行う関数の定義

import numpy as np

def cholesky(A,X,b):
    # 配列Aの大きさ
    N = len(A[0])
    # 修正コレスキー分解により、A=L*D*L_Tとなる変数。(L_TはLの転置行列)
    L = np.eye(N)
    L_T = L.T
    D = np.zeros((N, N))
    #Dの逆行列
    D_R = np.zeros((N, N))

    # 修正コレスキー分解
    for i in range(N):
        # Lの計算
        for j in range(i):
            l = A[i][j]
            for k in range(j):
                l -= L[i][k]*D[k][k]*L[j][k]
            L[i][j]= l/D[j][j] 
        # Ⅾの計算
        d = A[i][i]
        for k in range(i):
            d -= L[i][k]**2*D[k][k]
        D[i][i] = d

    # Y=D*L_T*XとなるY
    Y = np.zeros((N,1))

    # Yを前進代入により計算
    for i in range(N):
        y = b[i][0]
        for j in range(i): 
            y -= L[i][j] * Y[j][0]
        Y[i][0] = y

    #Dの逆行列を計算
    for i in range(N):
        if (D[i][i] != 0):
            D_R[i][i] = 1/D[i][i]
        else:
            D_R[i][i] = 0

    # Yに左からDの逆行列をかけた行列をZとして作成。これにより、L_T*X=Zとなり後退代入によりXが計算できる。
    Z = np.dot(D_R,Y)

    # 後退代入によりXを計算。
    for i in range(N-1, -1, -1):
        x = Z[i][0]
        for j in range(i+1, N):
            x -= L_T[i][j] * X[j][0]
        X[i] = x

    return X