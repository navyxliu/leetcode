// This is a trick we use to find intersection of two linked list.
// the LCA of Binary Tree is the same problem as it after we rotate two linked list 90' clockwise.
//
// we assume p is shorter than q:
// if we inspect those 2 paths, we will have this equation. our goal is find 'x'.
// a + c + x = b + c.
//
//    |a  |  c  |
//   p----
//        |-----root
//q-------
// |  b   |
//
// this is a trick called two pointers a and b.
// the trick here is that we redirect a to q when a hit the root. we redirect b to p when b hit the root.
// after then, a and b will meet at intersection, or lca in this case after x steps.
//
// Although the time complexity is same as hashtable, space complexity reduces to O(1).
class Solution {
public:
    // same as 160: Intersection of Two Linked Lists
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* a = p;
        Node* b = q;
        while (a != b) {
            a = a == nullptr ? q : a->parent;
            b = b == nullptr ? p : b->parent;
        }
        return a;
    }
}