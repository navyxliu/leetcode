class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> ans; 
        int sz1 = nums1.size(); int sz2 = nums2.size();
        if (sz1 == 0 || sz2 == 0) return ans; 
        
        vector<int> A2B(sz1, 0); 
        vector<int> B2A(sz2, 0);
        int i = 0; int j = 0;
        set<int> cache; 
        
        while (k-- > 0) {
            int t[2] = {INT_MAX, INT_MAX};
            int i1 = A2B[i];
            while (i < sz1 && i1 < sz2 && test(cache, i, i1)) {
                i1++; 
                
                if (i1 >= sz2) {
                    i1 = 0;
                    i++; 
                }
            }
            
            if (i < sz1 && i1 < sz2) {
                t[0] = nums1[i] + nums2[i1];
            }
            
            int j1 = B2A[j];
            while (j1 < sz1 && j < sz2 && test(cache, j1, j)) {
                j1++;
                
                if (j1 >= sz1){
                    j1 = 0;
                    j++;
                }
            }
            
            if (j1 < sz1 && j < sz2) {
                t[1] = nums1[j1] + nums2[j];
            }
            
            if (t[0] == t[1] && t[0] == INT_MAX) break;
            else if (t[0] < t[1]) {
                ans.push_back(make_pair(nums1[i], nums2[i1]));
                A2B[i] = max(A2B[i], i1+1);
                B2A[i1] = max(B2A[i1], i+1);
                cache.insert((i<<16)|i1);
                
                if (i1 + 1 >= sz2) i++; 
            }
            else {
                ans.push_back(make_pair(nums1[j1], nums2[j]));
                B2A[j] = max(B2A[j], j1+1);
                A2B[j1] = max(A2B[j1], j+1);      
                cache.insert((j1<<16)|j);

                if (j1 + 1 >= sz1) j++;
            }
        }
        return ans; 
    }
    bool test(set<int>& cache, int i, int j) {
        return cache.find((i<<16)|j) != cache.end();
    }
};
