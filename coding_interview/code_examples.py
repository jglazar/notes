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

# Treap
# Combines binary search tree with heap to provide probabilistic rebalancing
# Simpler than AVL or Red-Black trees, which require considering many cases
from random import random

class Node:
    def __init__(self, value):
        self.value = value
        self.priority = random()
        self.left = None
        self.right = None

def split(root, value):
    if (not root) or (not root.value):
        return None, None
    if value < root.value:
        left, root.left = split(root.left, value)
        return left, root
    root.right, right = split(root.right, value)
    return root, right

def merge(left, right):
    #Note: all left's values < all right's values 
    if (not left) or (not right):
        return left or right
    if left.priority < right.priority:
        left.right = merge(left.right, right)
        return left
    right.left = merge(left, right.left)
    return right

def insert(root, value):
    node = Node(value)
    left, right = split(root, value)
    return merge(merge(left, node), right)

def erase(root, value):
    left, right = split(root, value - 1)
    _, right = split(right, value)
    return merge(left, right)

# Skip list
# Linked list with random extra links for probabilistic binary search
# Provides simple alternative to balanced trees

from random import random

class Node():
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.forward = []

    @property
    def level(self) -> int:
        return len(self.forward)


class SkipList():
    def __init__(self, p, max_level = 16):
        self.head: Node()
        self.level = 0
        self.p = p
        self.max_level = max_level

    def __iter__(self):
        node = self.head
        while len(node.forward) != 0:
            yield node.forward[0].key
            node = node.forward[0]

    def random_level(self):
        level = 1
        while random() < self.p and level < self.max_level:
            level += 1
        return level

    def _locate_node(self, key):
        """
        :param key: Searched key,
        :return: Tuple with searched node (or None if given key is not present)
                 and list of nodes that refer (if key is present) of should refer to
                 given node.
        """
        # Nodes with refer or should refer to output node
        update_vector = []
        node = self.head
        for i in reversed(range(self.level)):
            # i < node.level - When node level is lesser than `i` decrement `i`.
            # node.forward[i].key < key - Jumping to node with key value higher
            #                             or equal to searched key would result
            #                             in skipping searched key.
            while i < node.level and node.forward[i].key < key:
                node = node.forward[i]
            # Each leftmost node (relative to searched node) will potentially have to
            # be updated.
            update_vector.append(node)
        update_vector.reverse()  # Note that we were inserting values in reverse order.
        # len(node.forward) != 0 - If current node doesn't contain any further
        #                          references then searched key is not present.
        # node.forward[0].key == key - Next node key should be equal to search key
        #                              if key is present.
        if len(node.forward) != 0 and node.forward[0].key == key:
            return node.forward[0], update_vector
        else:
            return None, update_vector

    def delete(self, key: KT):
        node, update_vector = self._locate_node(key)
        if node is not None:
            for i, update_node in enumerate(update_vector):
                # Remove or replace all references to removed node.
                if update_node.level > i and update_node.forward[i].key == key:
                    if node.level > i:
                        update_node.forward[i] = node.forward[i]
                    else:
                        update_node.forward = update_node.forward[:i]

    def insert(self, key: KT, value: VT):
        node, update_vector = self._locate_node(key)
        if node is not None:
            node.value = value
        else:
            level = self.random_level()

            if level > self.level:
                # After level increase we have to add additional nodes to head.
                for _ in range(self.level - 1, level):
                    update_vector.append(self.head)
                self.level = level

            new_node = Node(key, value)

            for i, update_node in enumerate(update_vector[:level]):
                # Change references to pass through new node.
                if update_node.level > i:
                    new_node.forward.append(update_node.forward[i])

                if update_node.level < i + 1:
                    update_node.forward.append(new_node)
                else:
                    update_node.forward[i] = new_node

    def find(self, key: VT) -> VT | None:
        node, _ = self._locate_node(key)
        if node is not None:
            return node.value
        return None

# Alternative implementation of skip list
from random import randint, seed

class Node:  
    def __init__(self, height = 0, elem = None):
        self.elem = elem
        self.next = [None]*height

class SkipList:

    def __init__(self):
        self.head = Node()
        self.len = 0
        self.maxHeight = 0

    def __len__(self):
        return self.len

    def find(self, elem, update = None):
        if update == None:
            update = self.updateList(elem)
        if len(update) > 0:
            item = update[0].next[0]
            if item != None and item.elem == elem:
                return item
        return None
    
    def contains(self, elem, update = None):
        return self.find(elem, update) != None

    def randomHeight(self):
        height = 1
        while randint(1, 2) != 1:
            height += 1
        return height

    def updateList(self, elem):
        update = [None]*self.maxHeight
        x = self.head
        for i in reversed(range(self.maxHeight)):
            while x.next[i] != None and x.next[i].elem < elem:
                x = x.next[i]
            update[i] = x
        return update
        
    def insert(self, elem):

        _node = Node(self.randomHeight(), elem)

        self.maxHeight = max(self.maxHeight, len(_node.next))
        while len(self.head.next) < len(_node.next):
            self.head.next.append(None)

        update = self.updateList(elem)            
        if self.find(elem, update) == None:
            for i in range(len(_node.next)):
                _node.next[i] = update[i].next[i]
                update[i].next[i] = _node
            self.len += 1

    def remove(self, elem):

        update = self.updateList(elem)
        x = self.find(elem, update)
        if x != None:
            for i in reversed(range(len(x.next))):
                update[i].next[i] = x.next[i]
                if self.head.next[i] == None:
                    self.maxHeight -= 1
            self.len -= 1            
                
    def printList(self):
        for i in range(len(self.head.next)-1, -1, -1):
            x = self.head
            while x.next[i] != None:
                print x.next[i].elem,
                x = x.next[i]
            print ''

# Also consider AA balancing trees, which are relatively simple
class AaTreeSet:
	def __init__(self, coll=None):
		self.clear()
		if coll is not None:
			for val in coll:
				self.add(val)
	
	def clear(self):
		self.root = AaTreeSet.Node.EMPTY_LEAF
		self.size = 0
	
	def __contains__(self, val):
		node = self.root
		while node is not AaTreeSet.Node.EMPTY_LEAF:
			if val < node.value:
				node = node.left
			elif val > node.value:
				node = node.right
			else:
				return True
		return False
	
	def add(self, val):
		if val in self:
			return
		self.root = self.root.add(val)
		self.size += 1
	
	def remove(self, val):
		self.root, found = self.root.remove(val)
		if not found:
			raise KeyError(str(val))
		self.size -= 1
	
	def discard(self, val):
		self.root, found = self.root.remove(val)
		if found:
			self.size -= 1
	
	# Note: Not fail-fast on concurrent modification.
	def __iter__(self):
		stack = []
		node = self.root
		while True:
			while node is not AaTreeSet.Node.EMPTY_LEAF:
				stack.append(node)
				node = node.left
			if len(stack) == 0:
				break
			node = stack.pop()
			yield node.value
			node = node.right

# For unit tests
	def check_structure(self):
		visited = set()
		if self.root.check_structure(visited) != self.size or len(visited) != self.size:
			raise AssertionError()
	
	class Node:
		def __init__(self, val=None):
			self.value = val
			if val is None:  # For the singleton empty leaf node
				self.level = 0
			else:  # Normal non-leaf nodes
				self.level = 1
				self.left  = AaTreeSet.Node.EMPTY_LEAF
				self.right = AaTreeSet.Node.EMPTY_LEAF
		
		def add(self, val):
			if self is AaTreeSet.Node.EMPTY_LEAF:
				return AaTreeSet.Node(val)
			if val < self.value:
				self.left = self.left.add(val)
			elif val > self.value:
				self.right = self.right.add(val)
			else:
				raise ValueError("Value already in tree")
			return self._skew()._split()  # Rebalance this node
		
		def remove(self, val):
			EMPTY = AaTreeSet.Node.EMPTY_LEAF
			if self is EMPTY:
				return (EMPTY, False)
			
			if val < self.value:
				self.left, found = self.left.remove(val)
			elif val > self.value:
				self.right, found = self.right.remove(val)
			else:  # Remove value at this node
				found = True
				if self.left is not EMPTY:
					# Find predecessor node
					temp = self.left
					while temp.right is not EMPTY:
						temp = temp.right
					self.value = temp.value  # Replace value with predecessor
					self.left, fnd = self.left.remove(self.value)  # Remove predecessor node
					assert fnd
				elif self.right is not EMPTY:
					# Find successor node
					temp = self.right
					while temp.left is not EMPTY:
						temp = temp.left
					self.value = temp.value  # Replace value with successor
					self.right, fnd = self.right.remove(self.value)  # Remove successor node
					assert fnd
				else:
					assert self.level == 1
					return (EMPTY, True)
			
			# Rebalance this node if a child was lowered
			if not found or self.level == min(self.left.level, self.right.level) + 1:
				return (self, found)
			if self.right.level == self.level:
				self.right.level -= 1
			self.level -= 1
			result = self._skew()
			result.right = result.right._skew()
			if result.right.right is not EMPTY:
				result.right.right = result.right.right._skew()
			result = result._split()
			result.right = result.right._split()
			return (result, True)
		
		#       |          |
		#   A - B    ->    A - B
		#  / \   \        /   / \
		# 0   1   2      0   1   2
		def _skew(self):
			assert self is not AaTreeSet.Node.EMPTY_LEAF
			if self.left.level < self.level:
				return self
			result = self.left
			self.left = result.right
			result.right = self
			return result
		
		#   |                      |
		#   |                    - B -
		#   |                   /     \
		#   A - B - C    ->    A       C
		#  /   /   / \        / \     / \
		# 0   1   2   3      0   1   2   3
		def _split(self):
			assert self is not AaTreeSet.Node.EMPTY_LEAF
			# Must short-circuit because if right.level < self.level, then right.right might not exist
			if self.right.level < self.level or self.right.right.level < self.level:
				return self
			result = self.right
			self.right = result.left
			result.left = self
			result.level += 1
			return result
		
		# For unit tests, invokable by the outer class.
		def check_structure(self, visitednodes):
			if self is AaTreeSet.Node.EMPTY_LEAF:
				return 0
			if self in visitednodes:
				raise AssertionError()
			visitednodes.add(self)
			
			value = self.value
			level = self.level
			left  = self.left
			right = self.right
			if value is None or left is None or right is None:
				raise AssertionError()
			if not (level > 0 and level == left.level + 1 and level - right.level in (0, 1)):
				raise AssertionError()
			if level == right.level and level == right.right.level:  # Must short-circuit evaluate
				raise AssertionError()
			if left != AaTreeSet.Node.EMPTY_LEAF and not (left.value < value):
				raise AssertionError()
			if right != AaTreeSet.Node.EMPTY_LEAF and not (right.value > value):
				raise AssertionError()
			
			size = 1 + left.check_structure(visitednodes) + right.check_structure(visitednodes)
			if not (2**level - 1 <= size <= 3**level - 1):
				raise AssertionError()
			return size

# Static initializer. A bit of a hack, but more elegant than using None values as leaf nodes.
AaTreeSet.Node.EMPTY_LEAF = AaTreeSet.Node()
