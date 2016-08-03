import sys

def merge(A, B):
     len1 = len(A)
     len2 = len(B)
     i = 0
     j = 0
     ans = []
     while i < len1 and j < len2:
          if (A[i] < B[j]):
               ans.append(A[i])
               i = i+1
          else:
               ans.append(B[j])
               j = j + 1

     if i < len1:
               ans.extend(A[i:])
     if j < len2:
               ans.extend(B[j:])
     return ans;

def abs(a):
  if a < 0: return -a
  else: return a

def findMinimalDiff(A, B):
  len1 = len(A)
  len2 = len(B)
  i = 0
  j = 0
  d = sys.maxint
  while i < len1 and j < len2:
    d = min(d, abs(A[i] -  B[j]))
    if A[i] < B[j]:
      i = i + 1
    else:
      j = j + 1    

  return d
 
if __name__ == "__main__":
  a = [1,3,3,4, 9]
  b = [6, 7, 10]
  ans = merge(a, b)
  print ans 
  print findMinimalDiff(a, b)
