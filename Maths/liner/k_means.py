#!/usr/bin/env python3

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.cluster import KMeans
from Bio.Cluster import kcluster

#模拟文档集合
corpus = ['I like great basketball game',
                    'This video game is the best action game I have ever played',
                    'I really really like basketball',
                    'How about this movie? Is the plot great?',
                    'Do you like RPG game?',
                    'You can try this FPS game',
                    'The movie is really great, so great! I enjoy the plot']

#把文本中的词语转换为词典和相应的向量
vectorizer = CountVectorizer()
vectors = vectorizer.fit_transform(corpus)

#输出所有的词条（所有维度的特征）
print('所有的词条（所有维度的特征）')
print(vectorizer.get_feature_names_out())
print('\n')

#输出(文章ID, 词条ID) 词频
print('(文章ID, 词条ID) 词频')
print(vectors)
print('\n')


#构建tfidf的值
transformer = TfidfTransformer()
tfidf = transformer.fit_transform(vectorizer.fit_transform(corpus))

# 输出每个文档的向量
tfidf_array = tfidf.toarray()
words = vectorizer.get_feature_names_out()

for i in range(len(tfidf_array)):
    print ("*********第", i + 1, "个文档中，所有词语的tf-idf*********")
    # 输出向量中每个维度的取值
    for j in range(len(words)):
        print(words[j], ' ', tfidf_array[i][j])
    print('\n')

####### 进行聚类，用欧氏距离
clusters = KMeans(n_clusters=3)
s = clusters.fit(tfidf_array)

#输出所有质心点，可以看到质心点的向量是组内成员向量的平均值
print('所有质心点的向量')
print(clusters.cluster_centers_)
print('\n')

#输出每个文档所属的分组
print('每个文档所属的分组')
print(clusters.labels_)

#输出每个分组内的文档
dict = {}
for i in range(len(clusters.labels_)):
    label = clusters.labels_[i]
    if label not in dict.keys():
        dict[label] = []
        dict[label].append(corpus[i])
    else:
        dict[label].append(corpus[i])
print(dict)

####### 进行聚类，用余弦夹角
clusterid, error, nfound  = kcluster(tfidf_array, nclusters=3, dist='u')
print(clusterid)
#输出每个分组内的文档
dict = {}
for i in range(len(clusterid)):
    label = clusterid[i]
    if label not in dict.keys():
        dict[label] = []
        dict[label].append(corpus[i])
    else:
        dict[label].append(corpus[i])
print(dict)