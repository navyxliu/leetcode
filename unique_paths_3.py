def newBoard(m, n):
  board = [[i*n + j + 1 for j in range(0, n)] for i in range(0,m)] 
  return board

def printBoard(b):
  for row in b:
    for col in row:
        print "%4d" % col,  
    print 

def backtrace(pi, x, y, m, n):
  path = []
  while x != 1 or y != 1:
    path.append((x-1) * n +y)
    x,y = pi[x][y]  

  path.append(1)
  path.reverse()
  return path

def unique_path_impl(ans, pi, x, y, m, n):
  if x == m and y == n:
    ans.append(backtrace(pi, x, y, m, n))
 
  if x < m:
    pi[x+1][y] = (x,y)
    unique_path_impl(ans, pi, x+1, y, m, n)

  if y < n:
    pi[x][y+1] = (x,y) 
    unique_path_impl(ans, pi, x, y+1, m, n)

def unique_path(m, n):
  ans = []
  pi = [[0 for j in range(0, n+1)] for i in range(0,m+1)] 
  unique_path_impl(ans, pi, 1, 1, m, n)
  return ans;

def countUniquePaths(m, n):
  d = [[0 for j in range(n)] for i in range(m)]
  d[0][0] = 1

  for i in range(1,m): d[i][0] = 1
  for j in range(1,n): d[0][j] = 1

  for i in range(1,m): 
    for j in range(1,n):
      d[i][j] = d[i-1][j] + d[i][j-1]

  return d[m-1][n-1]

if __name__ == "__main__":
  m, n = 3,7
  board = newBoard(m,n)
  printBoard(board)
  ans = unique_path(m, n)
  n = countUniquePaths(m, n)
  if len(ans) != n:
    print "wrong answer!"
  else:
    for i in ans:
      print i
  
