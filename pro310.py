class Node(object):
  def __init__(self, label):
      self.edges = []
      self.v= label

  def addEdge(self, node):
      self.edges.append(node)
  def numEdges(self):
      return len(self.edges)

class Solution(object):
    def findMinHeightTrees(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        G = [Node(i) for i in range(n)]
        if n == 1:
          return [0]

        for e in edges:
          i, j = e[0], e[1]
          G[i].addEdge(G[j])
          G[j].addEdge(G[i])
        
        leaves = []
        for i in range(n):
          if G[i].numEdges() == 1:
            leaves.append(G[i])
        print leaves

        while n > 2: 
          n = n - len(leaves);
          newLeaves = []

          for leaf in leaves:
            target = leaf.edges[0]
            target.edges.remove(leaf)

            if target.numEdges() == 1:
              newLeaves.append(target)  

          leaves = newLeaves;

        return [l.v for l in leaves]            

if __name__ == "__main__":
  sol = Solution()
  #n = 4
  #edges = [[1, 0], [1, 2], [1, 3]]
  #print sol.findMinHeightTrees(n, edges)

  #n = 6
  #edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
  #print sol.findMinHeightTrees(n, edges)

  n = 1
  edges = []
  print sol.findMinHeightTrees(n, edges)

