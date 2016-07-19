#include <forward_list>
#include <vector>
#include <utility>
using namespace std; 

struct Vertex {
    int id; 
    int degree; 
    forward_list<Vertex*> edges; 
    
    Vertex(int i) : id(i), degree(0) {}
    Vertex(): id(-1), degree(0) {}
    
    void addEdge(Vertex * tgt) {
        edges.push_front(tgt);
        degree++;
    }
};

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        vector<Vertex> G(n);
        vector<int> colors(n, 0);
        
        for (int i=0; i<n; ++i) G[i].id = i;
        
        for (auto & e: edges) {
            int x = e.first; 
            int y = e.second; 
            
            G[x].addEdge(&G[y]);
            G[y].addEdge(&G[x]);
        }
        
        int ans = 0;
        for (int i=0; i<n; ++i) if (colors[i] == 0) {
            ans++;
            dfs(&G[i], colors);
        }
        return ans; 
    }
    
    void dfs(Vertex * v, vector<int>& colors) {
        colors[v->id] = 1; 
        for (auto p : v->edges) {
            if (colors[p->id] == 0) dfs(p, colors);
        }
    }
};
