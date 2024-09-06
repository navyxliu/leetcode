#include <iostream>
#include <memory>
using namespace std;
// Leetcode 715: range-module
//
// Dynamic Segment tree
// 
// The root node is the biggest interval given by the problem domain. Instead of preallocating 
// an array to store all nodes in initialization, it dynamically materializes nodes on demand. 
//
// References: 
// 1. dynamic segment tree: https://cp-algorithms.com/data_structures/segment_tree.html#dynamic-segment-tree
// 2. optimization: https://walkccc.me/LeetCode/problems/0715/
// 3. https://lfool.github.io/LFool-Notes/algorithm/%E7%BA%BF%E6%AE%B5%E6%A0%91%E8%AF%A6%E8%A7%A3.html 
//
// remark
// Because the range is so big in this problem [1, 10^9], we would have Memory Limit Exceeded(MLE) if we render all nodes.
// One optimization I learnt from [2] is a) never extend tree in query b) prune children in update(). 

// Uncomment this to clean up all nodes. delete of C++ is so expensive that you may get TLE/MLE.
//#define CLEANUP_NODES

// gived by the problem
constexpr int RANGE_MIN = 1;
constexpr int RANGE_MAX = 1e9; 

class DynamicSegmentTree {
    struct Node {
        int   _lo; 
        int   _hi;
        bool  _value; // cover current range or not. 
        Node* _left    = nullptr; 
        Node* _right   = nullptr;
        
        Node(int lo, int hi, bool value): _lo(lo), _hi(hi), _value(value) {}

#ifdef CLEANUP_NODES
        ~Node() {
            // it's recursive and it's safe if children are nullptr
            delete _left; 
            delete _right;
        }
#endif        
    };

public:
    void update(int left, int right, bool value) {
        updateImpl(_root.get(), left, right, value);
    }

    bool query(int left, int right) {
        return queryImpl(_root.get(), left, right);
    }

    static DynamicSegmentTree* create(int left, int right) {
        return new DynamicSegmentTree(left, right);
    }
    
    DynamicSegmentTree() :  DynamicSegmentTree(RANGE_MIN, RANGE_MAX) {}

private:
    DynamicSegmentTree(int left, int right): _root(new Node(left, right, false)) {}

    void updateImpl(Node* node, int ql, int qr, bool value);
    bool queryImpl(Node* node, int ql, int qr);

    std::unique_ptr<Node> const _root; 
};

void DynamicSegmentTree::updateImpl(Node* node, int ql, int qr, bool value) {
    //cout << "update: " << "[" << ql << "," << qr << "] :=" << value << endl; 
    if (ql <= node->_lo && node->_hi <= qr) {
        node->_value = value; 

#ifdef CLEANUP_NODES        
        delete node->_left;
        delete node->_right; 
#endif
        // pruning children. all sub-intervals have the same value of node.
        node->_left = nullptr;
        node->_right = nullptr;
        return;
    }

    int mid = node->_lo + (node->_hi - node->_lo) / 2;

    // extend the tree
    if (node->_left == nullptr) {
        node->_left = new Node(node->_lo, mid, node->_value);
        node->_right = new Node(mid+1, node->_hi, node->_value);
    }

    if (ql <= mid) {
        updateImpl(node->_left, ql, qr, value);
    } 
    if (qr > mid) {
        updateImpl(node->_right, ql, qr, value);
    } 
    node->_value = node->_left->_value && node->_right->_value;
}

bool DynamicSegmentTree::queryImpl(Node* node, int ql, int qr) {    
    // pruned node. see comments in updateImpl()
    if (node->_left == nullptr) {
        return node->_value;
    }

    if (ql <= node->_lo && node->_hi <= qr) {
        return node->_value;
    }

    int mid = node->_lo + (node->_hi - node->_lo) / 2;
    
    int ans = true;
    if (ql <= mid) {
        ans = ans && queryImpl(node->_left, ql, qr);
    }
    if (qr > mid) {
        ans = ans && queryImpl(node->_right, ql, qr);
    }
    return ans;
}

class RangeModule {
    DynamicSegmentTree _segtree; 
    
public:
    RangeModule() {
    }
    
    void addRange(int left, int right) {
        // +1 to cover
        _segtree.update(left, right - 1, true);
    }
    
    bool queryRange(int left, int right) {
        return _segtree.query(left, right-1);
    }
    
    void removeRange(int left, int right) {
        _segtree.update(left, right-1, false);
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
int main() {
    
    {
    RangeModule mod;
    //["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]
    //[[],[10,20],[14,16],[10,14],[13,15],[16,17]]
    mod.addRange(10, 20);
    mod.removeRange(14, 16);
    std::cout << mod.queryRange(10, 14) << std::endl;
    std::cout << mod.queryRange(13, 15) << std::endl;
    std::cout << mod.queryRange(16, 17) << std::endl;
    }

    {
    //["RangeModule","addRange","removeRange","removeRange","addRange","removeRange","addRange","queryRange","queryRange","queryRange"]
    //[[],[6,8],[7,8],[8,9],[8,9],[1,3],[1,8],[2,4],[2,9],[4,6]]
        RangeModule mod; 
        //RangeModule mod; 
        cout << "addRange(6, 8)" << endl;  
        mod.addRange(6, 8);
        cout << "removeRange(7, 8)" << endl;
        mod.removeRange(7, 8);
        cout << "removeRange(8, 9)" << endl;
        mod.removeRange(8, 9);
        cout << "addRange(8, 9)" << endl;
        mod.addRange   (8, 9);
        cout << "removeRange(1,3)" << endl;
        mod.removeRange(1, 3);
        cout << "addRange(1, 8)" << endl;
        mod.addRange   (1, 8);

        cout << mod.queryRange(2, 4) << endl;
        cout << mod.queryRange(2, 9) << endl;
        cout << mod.queryRange(4, 6) << endl;
    }
 }