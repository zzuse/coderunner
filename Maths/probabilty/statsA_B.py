#!/usr/bin/env python3


import pandas as pd
from statsmodels.formula.api import ols
from statsmodels.stats.anova import anova_lm
import scipy.stats as ss


# 读取数据，d1对应于算法a，d2对应于算法b

df = pd.DataFrame({'algo':['a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'],'ratio':[ 0.29, 0.36, 0.32, 0.29, 0.34, 0.24, 0.27, 0.29, 0.31, 0.27, 0.29, 0.33, 0.31, 0.30, 0.31, 0.26, 0.25, 0.30, 0.28, 0.29]})
d1 = df[df['algo'] == 'a']['ratio']
d2 = df[df['algo'] == 'b']['ratio']


# 检测两个水平的正态性
print(ss.normaltest(d1))
print(ss.normaltest(d2))


# 检测两个水平的方差齐性
args = [d1, d2]
print(ss.levene(*args))


# F检验的第一种方法
print(ss.f_oneway(*args))


# F检验的第二种方法
model = ols('ratio ~ algo', df).fit()
anovat = anova_lm(model)
print(anovat)