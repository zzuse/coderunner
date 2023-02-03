#!/usr/bin/env python3
import random
import queue


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
            if friend_a_id == friend_b_id:
                continue
            print("relation ship: {} -- {}".format(friend_a_id, friend_b_id))
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
                print("Node {} has {} degree friends: {}".format(user_id, self.user_nodes[friend_id].degree, friend_id))
        if len(queue) <=0:
            print("Node {} no more friends".format(user_id))
            
    def get_next_degree_friend(self, que_in, visited_in):
        que_ret = queue.Queue()
        visited_ret = set()
        while not que_in.empty():
            cur_user_id = que_in.get()
            for friend_id in self.user_nodes[cur_user_id].friends:
                if visited_in.__contains__(friend_id):
                    continue
                que_ret.put(friend_id)
                visited_ret.add(friend_id)
        return que_ret, visited_ret
    
    def has_overlap(self, visited_a, visited_b):
        return len(visited_a & visited_b) > 0
        
    def bi_bfs_search(self, friend_a_id, friend_b_id):
        """
        bidirectional bfs search, to find shortest path between two user
        """
        if friend_a_id > len(self.user_nodes) or friend_b_id > len(self.user_nodes):
            return
        if friend_a_id == friend_b_id:
            return 0
        
        que_a = queue.Queue()
        que_b = queue.Queue()
        que_a.put(friend_a_id)
        que_b.put(friend_b_id)
        visited_a = set()
        visited_b = set()
        visited_a.add(friend_a_id)
        visited_b.add(friend_b_id)
        
        degree_a, degree_b, max_degree = 0, 0, 20
        while degree_a + degree_b < max_degree:
            degree_a += 1
            que_a, visited_a = self.get_next_degree_friend(que_a, visited_a)
            if self.has_overlap(visited_a, visited_b):
                print("user {} and {} have {} degree relation".format(friend_a_id, friend_b_id, degree_a + degree_b))
                return degree_a + degree_b
            degree_b += 1
            que_b, visited_b = self.get_next_degree_friend(que_b, visited_b)
            if self.has_overlap(visited_a, visited_b):
                print("user {} and {} have {} degree relation".format(friend_a_id, friend_b_id, degree_a + degree_b))
                return degree_a + degree_b
        return -1


if __name__ == "__main__":
    users = UserNodes(6)
    users.bfs_search(0)
    users.bi_bfs_search(0,5)