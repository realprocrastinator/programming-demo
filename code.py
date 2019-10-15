
import copy
# s1_ keeps stacking, s2 use to reverse the order
# whenever s1_ enque, update s2 for Deque constant time
class DQ:
    def __init__(self):
        # use two list as stack member
        self.s1_ = []
        self.s2 = []

    def Enqueue(self, e):
        self.s1_.append(e)
        s1_temp = copy.deepcopy(self.s1_) # s1_ needs to unchanged

        # pop s1_temp to s2_ s.t. order is right
        self.s2_ = [] #clear s2
        while s1_temp:
            self.s2_.append(s1_temp.pop())

    def Dequeue(self):
        # s2_ now maintain the right order of queque
        return self.s2_.pop()



dq = DQ()

dq.Enqueue(1)
dq.Enqueue(2)
dq.Enqueue(3)

print(dq.Dequeue())
print(dq.Dequeue())
print(dq.Dequeue())




