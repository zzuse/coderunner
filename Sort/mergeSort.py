#!/usr/bin/python
import time, random

def merge(a, start1, start2, end):
	index1 = start1
	index2 = start2
	'''length is the total length of two groups of number'''
	length = end - start1
	aux = [None] * length
	for i in range(length):
		'''two groups compare,merge to aux'''
		if ((index1 == start2) or
		'''if first group is bigger'''
			((index2 != end) and (a[index1] > a[index2]))):
			'''put in the smaller one'''
			aux[i] = a[index2]
			index2 += 1
		else:
			aux[i] = a[index1]
			index1 += 1
	'''put back from aux to original'''
	for i in range(start1, end):
		a[i] = aux[i - start1]

def mergeSort(a):
	n = len(a)
	step = 1
	while (step < n):
		for start1 in range(0, n, 2*step):
			start2 = min(start1 + step, n)
			'''end is 2-way merge scope'''
			end = min(start1 + 2*step, n)
			merge(a, start1, start2, end)
		'''from 2-way scan first'''
		step *= 2

a = [5,2,4,6,1,3]
startTime = time.time()
mergeSort(a)
endTime = time.time()
elapsedTime = endTime - startTime
print a
print("%20s n=%d  time =%6.3fs" % (mergeSort.__name__, len(a), elapsedTime))
