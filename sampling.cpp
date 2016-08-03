#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <set>

//return a random integer in [a,b]
int randint(int a, int b) {
  if (a > b) {
    std::swap(a, b);
  }  
  int n = (b-a+1);
  return a + (rand() % n);
}

//randomly select m element from n
//please note that n is known ahead. 
std::vector<int> select(int n, int m) {
  std::vector<int> ans; 
  int remaining = n; 
  int select = m; 

  for (int i=0; i<n; ++i) {
    int j = rand() % remaining; 
    if (j < select) {
      ans.push_back(i);
      select--;
    }
    remaining--;
  }

  return ans; 
}

//we don't know n ahead. assume n is a stream
std::vector<int> 
reservoir_sampling(int n, int m) {
  std::vector<int> reservoir(m);

  for (int i=0;i<m; ++i) reservoir[i] = i;

  for (int i=m; i<n; ++i) {
    int j = rand() % (i+1); //[0, i]

    if (j < m) {
      std::swap(reservoir[j], i);
    }
  } 

  return reservoir;
}

//if m is close to n.
std::vector<int> genFlody(int n, int m) {
  std::set<int> S;
  std::set<int>::iterator i;
  
  for (int j=n-m; j<n; ++j) {
    int t = rand() % (j+1);
    if (S.find(t) == S.end())  //t is not in S
      S.insert(t);
    else
      S.insert(j);
  }

  std::vector<int> ans; 
  for (auto v: S) {
    ans.push_back(v);
  }
  return ans; 
}
int main() {
  srand((unsigned)time(NULL));
  for (int i=0; i<10; ++i) {
    printf("%d\n", rand());
  }

  printf("dump 10 random in [1, 100]\n");
  for (int i=0; i<10; ++i) {
    printf("%d\n", randint(1, 100));
  } 
  
  int n = 1000;
  int m = 10;
  auto ans = select(n, m);
  printf("select %d from [0,%d)\n", m, n);
  for (auto v: ans) {
    printf(" %4d", v);
  }
  printf("\n");

  ans = reservoir_sampling(n, m);
  printf("select using reservoir sampling  %d from [0,%d)\n", m, n);
  for (auto v: ans) {
    printf(" %4d", v);
  }
  printf("\n");
  
  n = 30;
  m = 28;
  ans = genFlody(n, m);
  printf("select using flody set-based algorithm %d from [0,%d)\n", m, n);
  for (auto v: ans) {
    printf(" %4d", v);
  }
  printf("\n");


}

