import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn import datasets
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler

data_url = "http://lib.stat.cmu.edu/datasets/boston"
boston = pd.read_csv(data_url, sep="\s+", skiprows=22, header=None)
df_features = np.hstack([boston.values[::2, :], boston.values[1::2, :2]])
df_targets = boston.values[1::2, 2]

# boston = datasets.load_boston()
# df_features = pd.DataFrame(boston.data)
# df_targets = pd.DataFrame(boston.target)

print(boston)
print(df_features.shape)
print(df_targets.shape)
df_concat = pd.concat(
    [pd.DataFrame(df_features), pd.DataFrame(df_targets)], axis=1)
print(df_concat)

standardScaler = StandardScaler()  # 基于Z分数的标准化
standardScaler.fit(df_concat)
df_standardized = standardScaler.transform(df_concat)  # 对原始数据进行标准化，包括特征值和目标变量

df_features_standardized = df_standardized[:, 0:-1]  # 获取标准化之后的特征值
df_targets_standardized = df_standardized[:, -1]  # 获取标准化之后的特征值

# 再次进行线性回归
regression_standardized = LinearRegression().fit(
    df_features_standardized, df_targets_standardized)
print(regression_standardized.score(
    df_features_standardized, df_targets_standardized))
print(regression_standardized.coef_)

# 设置系数矩阵B
B = regression_standardized.coef_.reshape(
    len(regression_standardized.coef_), 1)

# 设置特征矩阵X
X = df_features_standardized

# 设置目标矩阵Y
Y = df_targets_standardized.reshape(len(df_targets_standardized), 1)

# 计算预测误差绝对值
E = np.dot(X, B) - Y

# 输出预测误差的平均值和方差
print('误差平均值=', np.mean(E))
print('误差的方差=', np.var(E))
