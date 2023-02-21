#!/usr/bin/env python3


import pandas as pd
from sklearn import datasets
from sklearn.preprocessing import scale
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import numpy as np

iris = datasets.load_iris()

species = [iris.target_names[x] for x in iris.target]

iris = pd.DataFrame(iris['data'], columns = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width'])
print(iris.describe().round(3))
iris['Species'] = species
print(iris)

def plot_iris(iris, col1, col2):
	sns.lmplot(x = col1, y = col2,
		data = iris,
		hue = "Species",
		fit_reg = False)
	plt.xlabel(col1)
	
	plt.ylabel(col2)
	
	plt.title('Iris species shown by color')
	
	plt.show()

iris['count'] = 1
print(iris[['Species', 'count']].groupby('Species').count())

num_cols = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width']

iris_scaled = scale(iris[num_cols])

iris_scaled = pd.DataFrame(iris_scaled, columns = num_cols)

print(iris_scaled.describe().round(3))

# 字符串转换成数字
levels = {'setosa':0, 'versicolor':1, 'virginica':2}

iris_scaled['Species'] = [levels[x] for x in iris['Species']]

print(iris_scaled.head())

# 分割成样本训练集和评估数据集
np.random.seed(3456)

iris_split = train_test_split(np.asmatrix(iris_scaled), test_size = 75)

iris_train_features = iris_split[0][:, :4]

iris_train_labels = np.ravel(iris_split[0][:, 4])

iris_test_features = iris_split[1][:, :4]

iris_test_labels = np.ravel(iris_split[1][:, 4])

print(iris_train_features.shape)

print(iris_train_labels.shape)

print(iris_test_features.shape)

print(iris_test_labels.shape)

plot_iris(iris, 'Petal_Width', 'Petal_Length')

plot_iris(iris, 'Sepal_Width', 'Sepal_Length')
