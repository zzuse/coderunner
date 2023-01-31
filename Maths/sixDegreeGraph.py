#!/usr/bin/env python3
import random

class Node:
    
    def __init__(self, userid):
        self.userid = userid  # 每个节点中存储一个字母
        self.friends = set()
        self.degree = 0
        

class UserNodes:
    
    def __init__(self, num):
        self.user_nodes = [ Node(i) for i in range(num) ]
        self.__generate_relation(num)

    def __generate_relation(self, num):
        for i in range(10):
            friend_a_id = random.randint(0,num-1)
            friend_b_id = random.randint(0,num-1)
            print(friend_a_id,friend_b_id)
            if friend_a_id == friend_b_id:
                continue
            self.user_nodes[friend_a_id].friends.add(friend_b_id)
            self.user_nodes[friend_b_id].friends.add(friend_a_id)

    def bfs_search(self, user_id):
        """
        * @Description:  通过广度优先搜索，查找好友
        * @param user_nodes-用户的结点；user_id-给定的用户ID，我们要为这个用户查找好友
        * @return void
        """
        if user_id > len(self.user_nodes):
            return
        
        queue = list()
        queue.append(user_id)
        
        visited = set()
        visited.add(user_id)
        
        while len(queue) > 0:
            cur_user_id = queue[0]
            queue = queue[1:]
            for friend_id in self.user_nodes[cur_user_id].friends:
                if visited.__contains__(friend_id):
                    continue
                queue.append(friend_id)
                visited.add(friend_id)
                self.user_nodes[friend_id].degree = self.user_nodes[cur_user_id].degree + 1
                print("{} degree friends: {}".format(self.user_nodes[friend_id].degree, friend_id))


if __name__ == "__main__":
    users = UserNodes(6)
    users.bfs_search(0)