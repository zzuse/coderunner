#!/usr/bin/env python3
import sys


"""
coins have 2,3,7 values, to get sum 100, calculate min coin numbers
"""
tmp_hash = [0] * (200 + 1)
def least_coins_recursion(total, coins):
	"""
	recursion, need hash map to speed up
	"""
	if total == 0:
		return 0
	if total < 0:
		return sys.maxsize
	global tmp_hash
	if tmp_hash[total] > 0 :
		min_coins = tmp_hash[total]
	else:
		tmp_coins_list = list()
		for j in coins:
			tmp_coins_list.append(1 + least_coins_recursion(total-j, coins))
		min_coins = min(tmp_coins_list)
	tmp_hash[total] = min_coins
	return min_coins


def least_coins_iteration(total, coins):
	"""
	iteration
	"""
	if min(coins) > total:
			return None
	# 每个额度的钱币数，初始化值为 None，假设不存在或无解
	dp = list([None]*(total+1))
	# 一些确定额度的钱币数
	dp[0] = 0
	for j in coins:
		if j <= total:
			dp[j] = 1
	# 动态规划求解钱币数
	for i in range(min(coins) + 1, total+1):
		tmp_count = list()  # 临时保存钱币数
		tmp_coins_list = [j for j in coins if j <= i]  # 求解 count[i-j] 时，i-j 大于 0
		for j in tmp_coins_list:
			if dp[i-j] is not None:
				tmp_count.append(dp[i-j])
		if len(tmp_count) > 0:
			dp[i] = min(tmp_count) + 1
			
	return dp[total]
	

if __name__ == "__main__":
	print("动态规划，最少钱币数：", least_coins_iteration(100, [2, 3, 7]))
	print("递归方法，最少钱币数：", least_coins_recursion(100, [2, 3, 7]))
	