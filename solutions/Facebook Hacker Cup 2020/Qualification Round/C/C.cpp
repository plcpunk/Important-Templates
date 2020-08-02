#include <iostream>
#include <set>
#include <unordered_map>
#define get(x) find(x)->second
using namespace std;

int main() {
  int t;
  cin>>t;
  set<int> positions;
  unordered_map<int, int> height;
  unordered_map<int, int> max_length;
  for(int testCase=1;testCase<=t;testCase++) {
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
      int p,h;
      cin>>p>>h;
      positions.insert(p);
      positions.insert(p+h);
      positions.insert(p-h);
      height[p] = h;
      max_length[p] = 0;
      max_length[p-h] = 0;
      max_length[p+h] = 0;
    }
    set<int>::iterator it;int ans = 0;
    for(it = positions.begin();it != positions.end();++it) {
      int p = *it;
      int m = max_length.get(p);
      if(height.find(p) != height.end()) {
        int h = height.get(p);
        max_length[p+h] = max(max_length.get(p+h), m + h);
        m = max(m, max_length.get(p-h) + h);
      }
      max_length[p] = m;
      ans = max(ans, m);
    }
    cout<<"Case #"<<testCase<<": "<<ans<<endl;
    positions.clear();
    height.clear();
    max_length.clear();
  }
  return 0;
}
