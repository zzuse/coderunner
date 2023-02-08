#!/usr/bin/env python3


import pandas as pd

from sklearn import datasets
iris = datasets.load_iris()

species = [iris.target_names[x] for x in iris.target]

iris = pd.DataFrame(iris['data'], columns = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width'])

iris['Species'] = species
print(iris)