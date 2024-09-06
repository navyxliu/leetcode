def lowestCommonAncestor(self, root, p, q):
    def path(root, goal):
        path, stack = [], [root]
        while True:
            node = stack.pop()
            if node:
                if node not in path[-1:]:
                    path += node,
                    if node == goal:
                        return path
                    stack += node, node.right, node.left
                else:
                    path.pop()
    return next(a for a, b in zip(path(root, p), path(root, q))[::-1] if a == b)


if __name__ == "__main__":
  pass 
