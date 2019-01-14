class ListNode:
    def __init__(self, x):
         self.val = x
         self.next = None
class Solution:
    def twoSum(self, nums, target):  #problem1
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        temp = set()
        for i, n in enumerate(nums):
            if (target - n) in temp:
                return [i, nums.index(target - n)]
            else:
                temp.add(n)
        #hashmap方法 50ms O(n)
    def addTwoNumbers(self, l1, l2 ,plus=0):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        if l1 or l2:
            temp=(l1.val if l1 else 0) + (l2.val if l2 else 0) + plus
            plusnew = temp // 10
            newnode=ListNode(temp%10)
            newnode.next = self.addTwoNumbers(l1.next if l1 else None,l2.next if l2 else None,plusnew)
            return newnode
        elif plus:
            return ListNode(1)
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        start=maxlen=0
        dict_temp={}
        for i in range(len(s)):
            if s[i] in dict_temp and start<=dict_temp[s[i]]:  #这个and很重要
                start=dict_temp[s[i]]+1
                dict_temp[s[i]]=i
            else:
                dict_temp[s[i]]=i
                maxlen = max(maxlen, i - start + 1)
        return maxlen
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        #核心思路，在两个数组之间用二分查找，找第k小
        k=len(nums1)+len(nums2)
        if k%2==1:
            return self.findKth(nums1, nums2,k//2+1)  #确保小的在前面
        else:
            res1=self.findKth(nums1,nums2,k/2)
            res2=self.findKth(nums1,nums2,k/2+1)
            return (res1+res2)/2
    def findKth(self,nums1,nums2,k): #to problem4
        if len(nums1)>len(nums2):
            return self.findKth(nums2,nums1,k)
        if len(nums1)==0:
            return nums2[int(k-1)]
        if k==1:
            return min(nums1[0],nums2[0])
        len1=int(min(k//2,len(nums1)))
        len2=int(k-len1)
        if nums1[len1-1]<nums2[len2-1]:
            nums1=nums1[len1:len(nums1)]
            nums2=nums2[0:len2]
            return self.findKth(nums1,nums2,k-len1)
        elif nums1[len1-1]>nums2[len2-1]:
            nums1 = nums1[0:len1]
            nums2=nums2[len2:len(nums2)]
            return self.findKth(nums1,nums2,k-len2)
        else:
            return nums1[len1-1]
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        strx=str(x)
        strout=""
        if strx[0]=='-':
            strout+='-'
            for i in range(len(strx)-1):
                strout+=strx[len(strx)-i-1]
        else:
            for i in range(len(strx)):
                strout+=strx[len(strx)-i-1]
        outnum=int(strout)
        if outnum<-pow(2,31) or outnum>pow(2,31)-1:
            return 0
        return outnum
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if x<0:
            return False
        a=0
        tmp=x
        while tmp>0:
            a=a*10+tmp%10
            tmp=tmp//10
        if a==x:
            return True
        else:
            return False

problem=9
solu=Solution()
if problem==1:
    print(solu.twoSum([2, 7, 11, 15],9))
elif problem==2:
    Node1_1 = ListNode(2)
    Node1_2 = ListNode(4)
    Node1_3 = ListNode(3)
    Node1_1.next = Node1_2
    Node1_2.next = Node1_3
    Node2_1 = ListNode(5)
    Node2_2 = ListNode(6)
    Node2_3 = ListNode(4)
    Node2_1.next = Node2_2
    Node2_2.next = Node2_3
    Node3_1 = ListNode(1)
    Node4_1 = ListNode(9)
    Node4_2 = ListNode(9)
    Node4_1.next=Node4_2
    newnode=solu.addTwoNumbers(Node3_1,Node4_1)
    while newnode!=None:
        print(newnode.val)
        newnode=newnode.next
elif problem==3:
    print(solu.lengthOfLongestSubstring("abba"))
elif problem==4:
    print(solu.findMedianSortedArrays([],[1,2,3, 4]))
elif problem==5:
    print(solu.longestPalindrome("abac"))
elif problem==7:
    print(solu.reverse(-123))
elif problem==9:
    print(solu.isPalindrome(121))