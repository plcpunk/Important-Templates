#include <iostream>
#include <deque>
#define INF 1000000000000000000LL
#define MAXVAL 10000000000000000LL
#define MAXN 1000000

using namespace std;

long long c[MAXN], dp[MAXN];

int main() {
  int t;
  deque<int> q;
  cin>>t;
  for(int testCase=1;testCase<=t;testCase++) {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) {
      cin>>c[i];
      if(c[i]==0) c[i] = INF;
    }
    c[0]=0;
    for(int i=0;i<m;i++) {
      dp[i]=0;
      while(!q.empty() and  c[i] <= c[q.back()]) q.pop_back();
       q.push_back(i);
    }
    for(int i=m;i<n;i++) {
      dp[i] = c[q.front()] + dp[q.front()];
      while(!q.empty() && q.front() <= i-m) q.pop_front();
      while(!q.empty() && c[i]+dp[i] <= c[q.back()]+dp[q.back()]) q.pop_back();
      q.push_back(i);
    }
    long long ans = dp[n-1];
    if(ans > MAXVAL || ans < 0) ans = -1;
    cout<<"Case #"<<testCase<<": "<<ans<<endl;
  }
  return 0;
}
