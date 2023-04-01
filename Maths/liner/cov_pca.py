import numpy as np
import pandas as pd
from numpy import linalg as LA
from sklearn.preprocessing import scale
from sklearn.decomposition import PCA
# 原始数据，包含了3个样本和3个特征，每一行表示一个样本，每一列表示一维特征
x = np.array([[1, 3, -7], [2, 5, -14], [-3, -7, 2]])
print("original\n", x)
# 矩阵按列进行标准化
x_s = scale(x, with_mean=True, with_std=True, axis=0)
print("按列标准化后的矩阵：\n", x_s)

# 计算协方差矩阵，注意这里需要先进行转置，因为这里的函数是看行与行之间的协方差
x_cov = np.cov(x_s.transpose())
# 输出协方差矩阵
print("协方差矩阵：\n", x_cov, "\n")

# 求协方差矩阵的特征值和特征向量
eigVals, eigVects = LA.eig(x_cov)
print("协方差矩阵的特征值：", eigVals)
print("协方差的特征向量（主成分）：\n", eigVects, "\n")

# 找到最大的特征值，及其对应的特征向量
max_eigVal = -1
max_eigVal_index = -1

for i in range(0, eigVals.size):
    if eigVals[i] > max_eigVal:
        max_eigVal = eigVals[i]
        max_eigVal_index = i
    eigVect_with_max_eigVal = eigVects[:, max_eigVal_index]

# 输出最大的特征值及其对应的特征向量，也就是第一个主成分
print("最大的特征值：", max_eigVal)
print("最大特征值所对应的特征向量：", eigVect_with_max_eigVal)

# 输出变换后的数据矩阵。注意，这里的三个值是表示三个样本，而特征从3维变为1维了。
# 原始的数据去左乘这个特征向量，来获取降维后的新数据, 找到了方向且保留了原始信息
print("变换后的数据矩阵：", x_s.dot(eigVect_with_max_eigVal), "\n")

################################
# 使用自带的PCA
# 挑选前2个主成分
pca = PCA(n_components=2)

# 进行PCA分析
pca.fit(x_s)

# 输出变换后的数据矩阵。注意，这里的三个值是表示三个样本，而特征从3维变为1维了。
print("自带PCA方差(特征值): ", pca.explained_variance_)
print("自带PCA主成分(特征向量)", pca.components_)
print("自带PCA变换后的样本矩阵:", pca.transform(x_s))
print("自带PCA信息量,它是各个主成分的方差所占的比例:", pca.explained_variance_ratio_)
