import numpy as np

# 设置确定随机跳转概率的alpha、网页结点数
alpha = 0.9
N = 5
# 迭代精度
delta_threshold = 1e-5 

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

# PageRank算法本身是采用迭代方式进行的，当最终的取值趋于稳定后结束。
i = 0
last_pr = None
while True:
    
    # 进行点乘，计算Σ(PR(pj)/L(pj))
    pr = np.dot(pr, adj)
    
    # 转置保存Σ(PR(pj)/L(pj))结果的矩阵，并增加长度为N的列向量，其中每个元素的值为1/N，便于下一步的点乘。
    pr_jump = np.full([N, 2], [[0, 1/N]])
    pr_jump[:,:-1] = pr.transpose() # 对倒数第二列赋值
    
    # 进行点乘，计算α(Σ(PR(pj)/L(pj))) + (1-α)/N)
    pr = np.dot(pr_jump, jump)
    
    # 归一化PageRank得分
    pr = pr.transpose()
    pr = pr / pr.sum()
    if last_pr is not None:
        delta = list(map(abs, (pr/last_pr)))  # last_pr 是前一次的值
        delta = abs(np.max(delta)-1)  # 最大误差的百分比
        if delta <= delta_threshold:
            break
        else:
            last_pr = pr.copy()
            i = i + 1
            print("round", i, pr)
            continue
    last_pr = pr.copy()
    i = i + 1
    print("round", i, pr)