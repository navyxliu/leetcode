// 1514. Path with Maximum Probability
//
// Dijkstra algorithm
// proof: our target is the maximum weights. Relaxing an edge discovers a bigger path toward the target. 
// A new edge(u, v) can only decrease the weights of a path.
// dist[v] <= dist[u] * prob[uv] 
// 
// This problem maps to the shortest path problem and no edge has negative weight. 
// 
#include "leetcode.hpp"

struct Vertex {
    double cost;
    int prev; // optional, but useful if we want to compose path
    Vertex(double cost, int prev): cost(cost), prev(prev) {}
    Vertex(): cost(0), prev(-1) {}
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<Vertex> distTo(n);
        vector<vector<pair<int, double>>> graph(n, vector<pair<int, double>>());

        for (int i = 0; i < edges.size(); ++i) {
            vector<int>& edge = edges[i];

            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(make_pair(v, succProb[i]));
            graph[v].push_back(make_pair(u, succProb[i]));
        }

        // custom less
        auto cmp = [&](int lhs, int rhs) {
            return distTo[lhs].cost < distTo[rhs].cost;
        };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp); // maxHeap
        distTo[start_node] = Vertex(1.0, start_node);
        pq.push(start_node);
        
        while (!pq.empty()) {
            int idx = pq.top();
            pq.pop();

            if (idx == end_node) {
                print_path(distTo, idx, start_node);
                return distTo[end_node].cost;
            }

            for (pair<int, double> edge: graph[idx]) {
                int dst = edge.first;
                double cost = edge.second;

                if (distTo[idx].cost * cost > distTo[dst].cost) {
                    distTo[dst].cost = distTo[idx].cost * cost;
                    distTo[dst].prev = idx;
                    pq.push(dst);
                }
            }

        }
        return 0;
    }
    
    void print_path(const vector<Vertex>& distTo, int idx, int start_node) {
        vector<int> path;
        stack<int> stack;
        // backtrack
        while (idx != start_node) {
            stack.push(idx);
            idx = distTo[idx].prev;
        }
        path.push_back(start_node);
        while (!stack.empty()) {
            path.push_back(stack.top());
            stack.pop();
        }

        if (path.size() > 0) {
            cout << path[0]; 
            for (int i =1; i < path.size(); ++i) {
                cout << " - " << path[i];
            }
            cout << endl;
        }
    }
};

int main() {
    Solution sol;
    // Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
    // Output: 0.25000
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
    vector<double> probs = {0.5,0.5,0.2};
    double ans = sol.maxProbability(n, edges, probs, 0/*start*/, 2/*end*/);
    cout << ans << endl;

    // Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
    // Output: 0.30000
    n = 3;
    edges = {{0,1},{1,2},{0,2}};
    probs = {0.5,0.5,0.3};
    ans = sol.maxProbability(n, edges, probs, 0/*start*/, 2/*end*/);
    cout << ans << endl;

    // Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
    // Output: 0.00000
    n = 3;
    edges = {{0, 1}};
    probs = {0.5};
    ans = sol.maxProbability(n, edges, probs, 0/*start*/, 2/*end*/);
    cout << ans << endl;
}