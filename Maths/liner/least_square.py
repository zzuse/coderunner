from numpy import *
import pandas as pd
# --- 增广矩阵
x = mat([[1, 0, 1], [1, 1, -1], [1, 2, 8]])
y = mat([[1.4], [-0.48], [13.2]])
print("X\n----------\n{}\n----------".format(x))
print("Y\n----------\n{}\n----------".format(y))

print("X矩阵的转置X'\n", x.transpose())
print("\nX'点乘X\n", x.transpose().dot(x))
print("\nX'X矩阵的逆\n", (x.transpose().dot(x)).I)

print("\nX'X矩阵的逆点乘X'\n", (x.transpose().dot(x)).I.dot(x.transpose()))
print("\n系数矩阵B\n", (x.transpose().dot(x)).I.dot(x.transpose()).dot(y))
print("\n")

df_features = pd.DataFrame(x)
df_targets = pd.DataFrame(y)

from sklearn.linear_model import LinearRegression
regression = LinearRegression().fit(df_features, df_targets)
print("拟合程度的好坏:{}".format(regression.score(df_features, df_targets)))
print("截距:{}".format(regression.intercept_))
print("对应系数:{}".format(regression.coef_))
