#!/usr/bin/env python3

comb = ['t1', 't2', 't3', 't4', 't5']
import copy

def combination(n, comb, result):
	
	if n == 0:
		print(result)
		return
	for i in comb:
		newResult = copy.copy(result)
		newComb = copy.copy(comb)
		newResult.append(i)
		newComb = list(set(newComb).difference(set(comb[:comb.index(i) + 1])))
		combination(n - 1, newComb, newResult)
		
combination(3, comb, [])

# set_A.difference(set_B) -- for (A - B)