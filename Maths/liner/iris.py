#!/usr/bin/env python3


import pandas as pd

from sklearn import datasets
iris = datasets.load_iris()

species = [iris.target_names[x] for x in iris.target]

iris = pd.DataFrame(iris['data'], columns = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width'])

iris['Species'] = species
print(iris)


def plot_iris(iris, col1, col2):
	import seaborn as sns
	import matplotlib.pyplot as plt
	
	sns.lmplot(x = col1, y = col2,
				data = iris,
				hue = "Species",
				fit_reg = False)
	
	plt.xlabel(col1)
	
	plt.ylabel(col2)
	
	plt.title('Iris species shown by color')
	
	plt.show()
	
plot_iris(iris, 'Petal_Width', 'Sepal_Length')

plot_iris(iris, 'Sepal_Width', 'Sepal_Length')


from sklearn.preprocessing import scale

num_cols = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width']

iris_scaled = scale(iris[num_cols])

iris_scaled = pd.DataFrame(iris_scaled, columns = num_cols)

print(iris_scaled.describe().round(3))