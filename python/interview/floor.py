
"""
Given an integer k and a binary search tree, find the floor
(less than or equal to) of k, and the ceiling (larger than or equal to)
of k. If either does not exist, then print them as None.
"""
class Node:
  def __init__(self, value):
    self.left = None
    self.right = None
    self.value = value

def findCeilingFloor(root_node, k, floor=None, ceil=None):
    temp_floor = None
    temp_ceil = None

    # find the floor first
    curr_node = root_node.left
    while curr_node:
        if curr_node.value <= k:
            temp_floor = curr_node.value
            break
        else:
            curr_node = curr_node.left # going smaller

    # we have now found the floor , goint to its right to find the ceiling
    # curr_node null meaning the smallest is not smaller than k
    # need to search the right side of the tree
    curr_node = root_node.right if not curr_node else curr_node.right
    while curr_node:
        if curr_node.value >=  k:
            temp_ceil = curr_node.value
            break
        else:
            curr_node = curr_node.right # going bigger

    return (temp_floor,temp_ceil)

  # Fill this in.

root = Node(8)
root.left = Node(4)
root.right = Node(12)

root.left.left = Node(2)
root.left.right = Node(6)

root.right.left = Node(10)
root.right.right = Node(14)

print(findCeilingFloor(root, 5))
# (4, 6)
