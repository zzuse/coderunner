
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn import datasets

boston = datasets.load_boston()
df_features = pd.DataFrame(boston.data)
df_targets = pd.DataFrame(boston.target)


regression = LinearRegression().fit(df_features, df_targets)        #使用特征和目标数据，拟合线性回归模型
print(regression.score(df_features, df_targets))    #拟合程度的好坏
print(regression.coef_)            #各个特征所对应的系


from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler

df_concat = pd.concat([df_features,df_targets],axis=1)

minMaxScaler = MinMaxScaler()       #基于min和max值的归一化

df_normalized = minMaxScaler.fit_transform(df_concat)  #对原始数据进行归一化，包括特征值和目标变量
df_features_normalized = df_normalized[:, 0:-1] #获取归一化之后的特征值
df_targets_normalized = df_normalized[:, -1]    #获取归一化之后的目标值

#再次进行线性回归
regression_normalized = LinearRegression().fit(df_features_normalized, df_targets_normalized)
print(regression_normalized.score(df_features_normalized, df_targets_normalized))
print(regression_normalized.coef_)


standardScaler = StandardScaler()    #基于Z分数的标准化

standardScaler.fit(df_concat)
df_standardized = standardScaler.transform(df_concat)  #对原始数据进行标准化，包括特征值和目标变量


df_features_standardized = df_standardized[:, 0:-1] #获取标准化之后的特征值
df_targets_standardized = df_standardized[:, -1]    #获取标准化之后的特征值


#再次进行线性回归
regression_standardized = LinearRegression().fit(df_features_standardized, df_targets_standardized)
print(regression_standardized.score(df_features_standardized, df_targets_standardized))
print(regression_standardized.coef_)

## 归一化 预测结果
#minMaxScaler_test = MinMaxScaler()
#df_test_normalized = minMaxScaler_test.fit_transform(df_test.astype(dtype=float))
#df_test_features_normalized = df_test_normalized[:, :]
#predicted_normalized = regression_normalized.predict(df_test_features_normalized)
#print("归一化预测结果与实际值的均方根误差：%s" % np.sqrt(np.mean((predicted_normalized - expected_test) ** 2)))
#
## 标准化 预测结果
#standardScaler_test = StandardScaler()
#standardScaler_test.fit(df_test.astype(dtype=float))
#df_test_standardized = standardScaler_test.transform(df_test.astype(dtype=float))
#df_test_features_standardized = df_test_standardized[:, :]
#predicted_standardized = regression_standardized.predict(df_test_features_standardized)
#print("标准化预测结果与实际值的均方根误差：%s" % np.sqrt(np.mean((predicted_standardized - expected_test) ** 2)))