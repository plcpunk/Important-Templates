#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
#include "templates/SegmentTree.h"

int leastPrime[1000009]={0};

class Custom_SegmentTree: public SegmentTree<int> {
	public:

	int combine(int x,int y)
	{
		return max(x,y);
	}

	int update_combine(int x,int y)
	{
		if(y==0)
			return x;
		return y;
	}

	int identity_element()
	{
		return 0;
	}

} t;

void init()
{
	leastPrime[1] = 1;
	for(int i=2;i<=1000000;i++)
	{
		for(int j=i;j<=1000000;j+=i)
		{
			if(leastPrime[j]==0)
				leastPrime[j] = i;
		}
	}
}

void solve_input()
{
	int n,m,a[100009],arr[100009];
	set<int> s;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		arr[i] = leastPrime[a[i]];
		if(a[i]!=1)
			s.insert(i);
	}
	t.construct_tree(arr,n);
	while(m--)
	{
		int type,l,r;
		scanf("%d%d%d",&type,&l,&r);
		if(type==0)
		{
			set<int>::iterator low = s.lower_bound(l-1),up = s.upper_bound(r-1);
			set<int>::iterator it = low;
			vector<set<int>::iterator> eraseElements;
			while(it!=up)
			{
				int i = *it;
				a[i] = a[i]/leastPrime[a[i]];
				if(a[i]==1)
					eraseElements.push_back(it);
				t.update(i,i,leastPrime[a[i]]);
				++it;
			}
			for(int i=0;i<eraseElements.size();i++)
				s.erase(eraseElements[i]);
		}
		else
			printf("%d ",t.query(l-1,r-1));
	}
	printf("\n");
}

int main()
{
	init();
	int t;
	cin>>t;
	while(t--)
		solve_input();
	return 0;
}