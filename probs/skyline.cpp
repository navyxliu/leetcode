#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std; 
struct _Point {
    int x; 
    int b;

    bool isLeft(vector<vector<int>>& buildings) {
        return buildings[b][0] == x; 
    }

    _Point(int i, int id) : x(i), b(id) {}
    _Point() {}
};
void foo() {}
void MyAssert(bool f, vector<int>& heap) {
  if (!f) {
    cout << "dump heap\n";
    for (auto v : heap) {
      cout << v << " "; 
    }
    cout << "\n"; 
    foo();
  }
  assert(f);
}
//min-heap priority Q
template <class T, class _Container = vector<T>, class _Compare = less<typename _Container::value_type>> 
class PrioQueue {
  _Container arr; 

public:
  void push(T e) {
    sanity_check();
    arr.push_back(e);
    siftUp(arr.size()-1);
  }  

  T pop() {
    T t = arr[0];
    arr[0] = arr.back();
    arr.pop_back();
    siftDown(0);

    return t; 
  }
  void dump() {
    cout << "dump heap\n";
    for (auto v : arr) {
      cout << v << " "; 
    }
    cout << "\n"; 

  }
  bool empty() {
    return arr.size() == 0;
  }

  void remove(T t) {
    sanity_check();
    int i = find(arr.begin(), arr.end(), t) - arr.begin();
    assert(i >= 0 && i < arr.size());
    swap(arr[i], arr[arr.size()-1]); 
    arr.pop_back();
    if (arr[i] < t) 
      siftDown(i);
    else 
      siftUp(i); 
  }
  void sanity_check() {
    int sz = arr.size();
    for (int i=1; i < sz; ++i ) {
      MyAssert((arr[(i-1)/2] >= arr[i]), arr);
    }
  }
  void siftUp(int i) {
    while (i > 0) {
      int p = (i-1)/2; 
      if (!_Compare()(arr[p], arr[i])) break;
      swap(arr[p], arr[i]);
      i = p;
    } 
    sanity_check();
  }

  void siftDown(int i) {
    int sz = arr.size(); 

    while (i*2+1 < sz) {
      int k = i * 2 + 1;
      if (k < sz-1 && _Compare()(arr[k], arr[k+1])) k++;
      if (!_Compare()(arr[i], arr[k])) break;

      swap(arr[i], arr[k]);
      i = k; 
    }
    sanity_check();
  }  
};


class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
      vector<pair<int, int>> ans; 
      int sz = buildings.size(); 
      if (sz == 0) return ans; 
 
      sort(buildings.begin(), buildings.end(), [](const vector<int>& b1, const vector<int>& b2) {
                        return b1[2] == b2[2]  ? b1[0] < b2[0] : b1[2] < b2[2];  
                      });
      vector<vector<int>> strip; 

      int prev = buildings[0][2];
      strip.push_back(buildings[0]);
      for (int i=1; i<sz; ++i) {
        int h = buildings[i][2];
        if (h != prev) {
          prev = h; 
          strip.push_back(buildings[i]); 
        }
        else {
          vector<int>& last = strip.back();
          if (buildings[i][0] <= last[1]) {
            if (buildings[i][1] > last[1]) 
              last[1] = buildings[i][1];
          }
          else {
            strip.push_back(buildings[i]);
          }
        } 
      }
      swap(buildings, strip);
      sz = buildings.size();
      vector<_Point> points(2*sz); 

      for (int i=0; i<sz; ++i) {
        int j = i <<1;
        const vector<int>& b = buildings[i];
        points[j] = _Point(b[0], i);
        points[j+1] = _Point(b[1], i);
      }

      sort(points.begin(), points.end(), [](const _Point& p1, const _Point& p2) { return p1.x < p2.x; }); 
#if 0
      cout << "points size = " << points.size() << "\n";
      for (auto & p : points) {
        if (p.isLeft(buildings))
            cout << "[" << p.x << ", " << buildings[p.b][2] << " ";
        else 
            cout << " " << p.x << ", " << buildings[p.b][2] << "] ";
      }
      cout << "\n";
#endif
      int hi = 0;
      PrioQueue<int, vector<int>, less<int>> Q; 

      for (auto& p: points) {
        int h = buildings[p.b][2];

        if (p.isLeft(buildings)) {
          if(h > hi) {
            if (hi > 0) 
                Q.push(hi); 
            if (ans.size() > 0 && ans.back().first == p.x)
              ans.back().second = h; 

            else if (ans.size() == 0 || ans.back().second != h) {
              if (p.x == 889344) cout << "inserting: here (" << p.x << ", " << h << ")\n";
              ans.push_back(make_pair(p.x, h));
            }
            hi = h;
          }
          else {
            Q.push(h);
          }
        }  
        else {
          if (Q.empty()) {
            ans.push_back(make_pair(p.x, 0));
            hi = 0;
          }
          else {
            if (hi == h) {
              hi  = Q.pop();
              if (ans.size() ==  0 || ans.back().second != hi) {
                ans.push_back(make_pair(p.x, hi));
              }
            } 
            else {
              Q.remove(h);        
            }
          }
        }
      }     

      return ans; 
    }
};
void printOut(const string& msg, const vector<pair<int, int>>& ans) {
  cout << msg << " : ";
 
  cout << "["; 
  for (auto v : ans) {
    cout << "[" << v.first << "," << v.second << "], ";
  }
  cout << "]\n";

}

void test1() {
  vector<vector<int>> buildings = {{2,9,10}}; 
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test1", ans);
}

void test2() {
  vector<vector<int>> buildings = {{2,9,10}, {3,7,15}, {5,12,12}, {15,20,10}, {19,24,8}}; 
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test2", ans);
}
void test3() {
  vector<vector<int>> buildings = {{0,2,3}, {2,5,5}}; 
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test3", ans);
  vector<vector<int>> in2 = {{0,2,3}, {2,5,1}}; 
  ans = sol.getSkyline(in2);
  printOut("test3-2", ans); 
  vector<vector<int>> in3 = {{0,2,3}, {2,5,3}}; 
  ans = sol.getSkyline(in3);
  printOut("test3-3", ans);
  vector<vector<int>> in4 = {{0,5,3}, {2,10,3}}; 
  ans = sol.getSkyline(in4);
  printOut("test3-4", ans);
  vector<vector<int>> in5 = {{0,5,3}, {2,4,3}}; 
  ans = sol.getSkyline(in5);
  printOut("test3-5", ans);
  vector<vector<int>> in6 = {{0,2,3}, {2,4,3}, {7, 10, 1}, {4, 6, 3}, {6, 8, 5}}; 
  ans = sol.getSkyline(in6);
  printOut("test3-6", ans);
}
void test4() {
  vector<vector<int>> buildings = {{1, 10, 10}};
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test4", ans);
  
}
void test5() {
  vector<vector<int>> buildings = {{5951,42679,584900},{7612,460224,165719},{10054,528935,547159},{12434,184263,538819},{14903,205061,507630},{30168,640118,643081},{52730,67749,544684},{56208,347295,318255},{57296,500861,788192},{65779,535324,564426},{69626,936712,415579},{77787,785719,327931},{82254,805279,920649},{86518,383868,930470},{87489,418143,10692},{98967,724391,93083},{99745,742397,134090},{101345,176839,627338},{116139,360005,261692},{118986,130026,582543},{122923,470827,554902},{123305,124192,200341},{125932,726376,657081},{137743,889344,943207},{143009,468012,356768},{144978,404082,31802},{146685,244171,473528},{152385,835275,67458},{159945,571319,499254},{160872,908174,692144},{164623,315507,76118},{177782,386719,229831},{180448,787809,497368},{186034,256757,542791},{188402,843895,494935},{197303,894782,801283},{202312,261398,307960},{202390,308850,114020},{216466,587906,560282},{254738,444539,769109},{275954,456722,435187},{278192,586784,83534},{279840,472712,598594},{287433,876565,846065},{318879,922949,183256},{337738,845315,912970},{344100,965430,103653},{350296,779286,126824},{366521,400209,4075},{367676,911181,784590},{371269,947782,560479},{377942,978066,660521},{402938,794535,521823},{407536,929952,795747},{409959,457637,251645},{417770,838407,530482},{425965,790228,56305},{439707,961265,137333},{446176,513487,141989},{455879,582111,663768},{472532,567342,107840},{492380,561017,757035},{497930,603380,454255},{504632,534547,694128},{512389,594618,356728},{520832,931989,768018},{525637,997553,817328},{535984,566145,926744},{569708,631488,207038},{583058,918142,600957},{583928,806005,34478},{591010,851424,292990},{608726,998069,42301},{610001,658217,97268},{615495,785912,300917},{650994,896338,60267},{693313,726376,583178},{706898,791076,724417},{709816,928183,750769},{719093,753014,698100},{720242,773502,113359},{742290,807067,286960},{754791,832571,262145},{763308,855300,66229},{785215,909931,2177},{787290,818298,269345}};
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test5", ans);
}
void test6() {
  vector<vector<int>> buildings = {{1,10001,10000},{2,10001,9999},{3,10001,9998},{4,10001,9997},{5,10001,9996},{6,10001,9995},{7,10001,9994},{10,10001,9991},{10000,10001,1}};
  Solution sol; 
  auto ans = sol.getSkyline(buildings);
  printOut("test6", ans);
}

int main() {
  //test1();
  //test2();
  //test3();
  //test4();
  //test5();
  test6();
  return 0;
}
