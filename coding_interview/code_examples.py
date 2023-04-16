# Leetcode divide and conquer

def BinarySearch():

    class Problem:
        def __init__(self, nums, target):
            self.nums = nums
            self.target = target
    
    # class Solution is raw bool
    
    # not really needed bc divide only returns 1 subproblem
    def merge(ss):# list[bool]) -> bool:
        return ss[0]
    
    # the list will only have 1 subproblem
    def divide(p: Problem): #-> List[Problem]:
        a = p.nums[:len(p.nums)//2]
        b = p.nums[len(p.nums)//2:]
        if a[-1] < target:
            return [Problem(b, p.target)]
        return [Problem(a, p.target)]
    
    def f(p: Problem) -> bool:
        if not p.nums:
            return False
        if len(p.nums) == 1 and p.nums[0] == p.target:
            return True
        if len(p.nums) == 1 and p.nums[0] != p.target:
            return False
        return merge([f(pl) for pl in divide(p)])
    
    nums = [1,2,3,4,5,6]
    target = 8
    print(f"binary search test -- search for {target} in {nums}")
    print(f(Problem(nums,target)))
    
#BinarySearch()

def QuickSort():

    ## Problem and Solution are both just lists

    def merge(ss):
        return ss[0] + ss[1] + ss[2]

    def divide(p):
        pivot = p[0]
        left  = [x for x in p if x < pivot]
        equal = [x for x in p if x == pivot]
        right = [x for x in p if x > pivot]
        return [left, equal, right]

    def f(p):
        if len(p) <= 1:
            return p
        pl = divide(p)
        return merge([f(pl[0]), pl[1], f(pl[2])])

    nums = [1,2,4,3,5,2]
    print(f"quick sort test -- sort {nums}")
    print(f(nums))

#QuickSort()
