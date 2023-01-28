#!/usr/bin/env python3


class TrieNode:

	def __init__(self, letter):
		self.letter = letter  # 每个节点中存储一个字母
		self.childnode = [None] * 26
		self.isend = False    # isend表示单词是否结束


class TrieTree:
	"""
		must be lowercase letters
	"""
	def __init__(self):
		self.root = TrieNode('/')

	def insert(self, word):
		p = self.root
		for w in word:
			childnode = p
			index = ord(w) - ord('a')
			if p.childnode[index] == None:
				p.childnode[index] = TrieNode(w)
			p = p.childnode[index]
		p.isend = True
		
	def find(self, word):
		p = self.root
		for w in word:
			index = ord(w) - ord('a')
			if p.childnode[index] == None:
				return False
			p = p.childnode[index]
		if not p.isend:
			return False
		else:
			return True
	
	def startswith(self, prefix):
		p = self.root
		for w in prefix:
			index = ord(w) - ord('a')
			if p.childnode[index] == None:
				return False
			p = p.childnode[index]
		return True
	
	def dfs_travel(self):
		stack = []
		stack.append(self.root)
		output = []
		
		while len(stack) > 0:
			node = stack.pop()
			if node.letter:
				if node.letter is not '/':
					output.append(node.letter)
				if node.isend is True:
					print("{} ".format("".join(output)))
					clear = True
					for child in node.childnode:
						if child is not None:
							clear = False
					if clear:
						output.clear()
			for child in node.childnode:
				if child is not None:
					stack.append(child)
		
	
	
if __name__ == "__main__":
	trie = TrieTree()
	trie.insert("apple")
	print("insert apple \n")
	print("find apple {}\n".format(trie.find("apple")))
	print("find app {}\n".format(trie.find("app")))
	print("startswith app {}\n".format(trie.startswith("app")))
	trie.insert("app")
	print("insert app \n")
	print("find app {}\n".format(trie.find("app")))
	trie.insert("boy")
	trie.dfs_travel()

		