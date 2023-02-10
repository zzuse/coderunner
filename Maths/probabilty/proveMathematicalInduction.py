#!/usr/bin/env python3
#-*- coding:UTF-8 -*-
class result(object):
	wheatNum = 0
	wheatTotalNum = 0
	
class getWheatTotalNum(object):
	'''
	函数说明：使用递归嵌套， 进行数学归纳法证明
	Param： k - 表示放到第几格   result - 表示当前格子的麦粒数
	Return: boolean - 放到第K格时是否成立
	'''
	def prove(self, k, result):
		if k == 1:
			if (2 ** 1 - 1) == 1:
				result.wheatNum = 1
				result.wheatTotalNum = 1
				return True
			else:
				return False 
			
		else:
			proveOfPreviousOne = self.prove(k - 1, result)
			result.wheatNum *= 2
			result.wheatTotalNum += result.wheatNum
			proveOfCurrentOne = False
			if result.wheatTotalNum == (2 ** k - 1):
				proveOfCurrentOne = True
			if (proveOfPreviousOne & proveOfCurrentOne):
				return True
			else:
				return False
			
			
if __name__ == '__main__':
	grid = 64
	result = result()
	g = getWheatTotalNum()
	print(g.prove(grid, result))