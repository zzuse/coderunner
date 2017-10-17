#!/usr/bin/python
import time, random

def swap(a, i, j):
	(a[i], a[j]) = (a[j], a[i])
def bubbleSort(a):
	n = len(a)
	end = n
	swapped = True
	while (swapped):
		swapped = False
		for i in range(1, end):
			if (a[i-1] > a[i]):
				swap(a, i-1, i)
				swapped = True
		end -= 1

a = [5,2,4,6,1,3]
startTime = time.time()
bubbleSort(a)
endTime = time.time()
elapsedTime = endTime - startTime
print a
print("%20s n=%d  time =%6.3fs" % (bubbleSort.__name__, len(a), elapsedTime))
