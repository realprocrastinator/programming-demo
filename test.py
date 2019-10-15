#!/bin/python3


import math
import os
import random
import re
import sys
import collections
from collections import defaultdict
import math


def choose(n,k): #n choose k
    return math.factorial(n)/(math.factorial(k)*math.factorial(n-k))

# Complete the countTriplets function below.
def countTriplets(arr, r):
    counter = 0 #counter the number that would form the chain of mutiple of r
    total = 0  #record the total
    num_ind = {}

    #build a dict of number with all occurance of indece {num:[index1,index2,..],..}
    for i,e in enumerate(arr):
        num_ind.setdefault(e,[]).append(i)
    print("num_ind: ",num_ind)

    #special case of when r = 1
    #then need to find all triplet of the same
    if(r == 1):
        for e in num_ind:
            if(len(num_ind[e])>= 3): total += choose(len(num_ind[e]),3)
        return int(total)
 
    #from small to large and find possible triple
    for e in sorted(num_ind.keys()):
        curr = e #keep track the current multiple
        #level = {0:[index1,index2,..]..} level 0 index must be smaller than higher level
        level = {} #keep track of different bucket index list
        level[counter] = num_ind[curr]
        while r*curr in num_ind and counter < 2: #one more element satisfying the conidition
            counter += 1
            curr = curr*r
            level[counter] = num_ind[curr]

        #now must have reached counter of 3 reset counter and continue next element
        if(counter == 2): #enough to form tripplet
            #now we have leagel potential triplet of levels
            #need to satisfy index in lower level should be lower
            #all the indx in level 1 greater than in index 0
            #find out each element in level 1 is greater than how many in level 0
            greater_1 = defaultdict(int)
            for l_1 in level[1]:
                for l_0 in level[0]:
                    if l_1 > l_0: greater_1[l_1] +=1
            
            #now find each index in level 2, adding up freq in level 1 that it is greater than
            for l_2 in level[2]:
                for g1 in greater_1:
                    if l_2 > g1: total += greater_1[g1]
        counter  = 0 #reset counter for the next element
    
    return total



if __name__ == '__main__':
    nr = input().rstrip().split()

    n = int(nr[0])

    r = int(nr[1])

    arr = list(map(int, input().rstrip().split()))

    ans = countTriplets(arr, r)
    print(ans)
    print(2325652489)


