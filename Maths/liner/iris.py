#!/usr/bin/env python3


import pandas as pd
from sklearn import datasets
from sklearn.preprocessing import scale
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import numpy as np
from sklearn.neighbors import KNeighborsClassifier

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

# plot_iris(iris, 'Petal_Width', 'Sepal_Length')

# plot_iris(iris, 'Sepal_Width', 'Sepal_Length')

KNN_mod = KNeighborsClassifier(n_neighbors = 3)

KNN_mod.fit(np.asarray(iris_train_features), np.asarray(iris_train_labels))

iris_test = pd.DataFrame(iris_test_features, columns = num_cols)

iris_test['predicted'] = KNN_mod.predict(np.asarray(iris_test_features))

iris_test['correct'] = [1 if x == z else 0 for x, z in zip(iris_test['predicted'], iris_test_labels)]

accuracy = 100.0 * float(sum(iris_test['correct'])) / float(iris_test.shape[0])

print(accuracy)

levels = {0:'setosa', 1:'versicolor', 2:'virginica'}

iris_test['Species'] = [levels[x] for x in iris_test['predicted']]

markers = {1:'^', 0:'o'}

colors = {'setosa':'blue', 'versicolor':'green',}

def plot_shapes(df, col1,col2,  markers, colors):
	
	ax = plt.figure(figsize=(6, 6)).gca() # define plot axis
	
	for m in markers: # iterate over marker dictioary keys
		for c in colors: # iterate over color dictionary keys
			df_temp = df[(df['correct'] == m)  & (df['Species'] == c)]
			sns.regplot(x = col1, y = col2,
						data = df_temp, 
						fit_reg = False,
						scatter_kws={'color': colors[c]},
						marker = markers[m],
						ax = ax)
	plt.xlabel(col1)
	plt.ylabel(col2)
	plt.title('Iris species by color')
	plt.show()

plot_shapes(iris_test, 'Petal_Width', 'Sepal_Length', markers, colors)
plot_shapes(iris_test, 'Sepal_Width', 'Sepal_Length', markers, colors)
