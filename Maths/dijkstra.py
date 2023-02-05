#!/usr/bin/env python3
import random
import queue


class Node:

    def __init__(self, geoid):
        self.geoid = geoid  # location id
        self.closeby_weight = dict()


class Graph:

    def __init__(self, geo_num, closeby_num):
        self.geo_nodes = [ Node(i) for i in range(geo_num) ]
        self.__generate_relation(geo_num, closeby_num)
        
    def __generate_relation(self, geo_num, closeby_num):
        for i in range(closeby_num):
            geo_a_id = random.randint(0,geo_num-1)
            geo_b_id = random.randint(0,geo_num-1)
            if geo_a_id == geo_b_id:
                continue
            print("relation ship: {} --> {}".format(geo_a_id, geo_b_id))
            self.geo_nodes[geo_a_id].closeby_weight[geo_b_id] = round(random.random() ,2)
            
    def __craft_relation(self):
        self.geo_nodes[0].closeby_weight[]