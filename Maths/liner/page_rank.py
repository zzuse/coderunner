import numpy as np

# 设置确定随机跳转概率的alpha、网页结点数
alpha = 0.9
N = 5

# 初始化随机跳转概率的矩阵
jump = np.full([2,1], [[alpha], [1-alpha]], dtype=float)

# 邻接矩阵的构建
adj = np.full([N,N], [[0,0,1,0,0],[1,0,1,0,0],[1,0,0,0,0],[0,0,0,0,0],[0,1,0,0,0]], dtype=float)

# 对邻接矩阵进行归一化
row_sums = adj.sum(axis=1)      # 对每一行求和
row_sums[row_sums == 0] = 0.1   # 防止由于分母出现0而导致的Nan
adj = adj / row_sums[:, np.newaxis] # 除以每行之和的归一化 newaxis 1D array will become 2D array

# 初始的PageRank值，通常是设置所有值为1.0
pr = np.full([1,N], 1, dtype=float)