#!/usr/bin/python
import time, random

def swap(a, i, j):
	(a[i], a[j]) = (a[j], a[i])
def selectionSort(a):
	n = len(a)
	for startIndex in range(n):
		minIndex = startIndex
		for i in range(startIndex+1, n):
			if (a[i] < a[minIndex]):
				minIndex = i
		swap(a, startIndex, minIndex)

a = [5,2,4,6,1,3]
startTime = time.time()
selectionSort(a)
endTime = time.time()
elapsedTime = endTime - startTime
print a
print("%20s n=%d  time =%6.3fs" % (selectionSort.__name__,len(a), elapsedTime))
