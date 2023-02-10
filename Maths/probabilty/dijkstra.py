#!/usr/bin/env python3
import random
import queue
import sys


class Node:

    def __init__(self, geoid):
        self.geoid = geoid  # location id
        self.closeby_weight = dict()


class Graph:

    def __init__(self, geo_num):
        self.geo_nodes = [ Node(i) for i in range(geo_num) ]

    def generate_relation(self, geo_num, closeby_num):
        """
        not used
        """
        for i in range(closeby_num):
            geo_a_id = random.randint(0,geo_num-1)
            geo_b_id = random.randint(0,geo_num-1)
            if geo_a_id == geo_b_id:
                continue
            print("relationship: {} --> {}".format(geo_a_id, geo_b_id))
            if self.geo_nodes[geo_a_id].closeby_weight.get(geo_b_id) is not None:
                continue
            self.geo_nodes[geo_a_id].closeby_weight[geo_b_id] = round(random.random() ,2)
            
    def craft_relation(self):
        self.geo_nodes[0].closeby_weight[1] = 0.5
        self.geo_nodes[0].closeby_weight[2] = 0.3
        self.geo_nodes[0].closeby_weight[3] = 0.2
        self.geo_nodes[0].closeby_weight[4] = 0.4
        self.geo_nodes[1].closeby_weight[5] = 0.3
        self.geo_nodes[2].closeby_weight[1] = 0.2
        self.geo_nodes[2].closeby_weight[6] = 0.1
        self.geo_nodes[3].closeby_weight[6] = 0.4
        self.geo_nodes[3].closeby_weight[8] = 0.8
        self.geo_nodes[4].closeby_weight[3] = 0.1
        self.geo_nodes[4].closeby_weight[8] = 0.6
        self.geo_nodes[5].closeby_weight[7] = 0.1
        self.geo_nodes[6].closeby_weight[5] = 0.1
        self.geo_nodes[6].closeby_weight[8] = 0.2
        self.geo_nodes[8].closeby_weight[7] = 0.4
        
    def do_dijkstra(self, source_geo_id):
        F = set()
        F.add(source_geo_id)
        min_weight = [0] * len(self.geo_nodes)
        for i in range(len(self.geo_nodes)):
            if i == source_geo_id: 
                min_weight[i] = 0
            else:
                min_weight[i] = sys.maxsize
        
        self.update_weight(source_geo_id, min_weight)
        
        while len(F) < len(self.geo_nodes):
            geo_with_min_weight = self.find_geo_with_min_weight(min_weight, F)
            if geo_with_min_weight == -1 or geo_with_min_weight >= len(self.geo_nodes):
                break
            F.add(geo_with_min_weight)
            self.update_weight(geo_with_min_weight, min_weight)
        
        for a in range(len(min_weight)):
            print("start from {} and end at {} have least distance {}".format(source_geo_id, a, min_weight[a]))
            
    def update_weight(self, geo_id, min_weight):
        for key in self.geo_nodes[geo_id].closeby_weight.keys():
            new_weight = round(min_weight[geo_id] + self.geo_nodes[geo_id].closeby_weight[key],2)
            if new_weight < min_weight[key]:
                min_weight[key] = new_weight
                
    def find_geo_with_min_weight(self, min_weight, F):
        geo_with_min_weight = -1
        min_w = sys.maxsize
        for i in range(len(min_weight)):
            if F.__contains__(i):
                continue
            if min_weight[i] < min_w:
                min_w = min_weight[i]
                geo_with_min_weight = i
        return geo_with_min_weight


if __name__ == "__main__":
    geo_nodes1 = Graph(9)
    geo_nodes1.craft_relation()
    geo_nodes1.do_dijkstra(0)