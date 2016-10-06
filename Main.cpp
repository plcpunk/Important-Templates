#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#include "templates/PersistentTree.h"
#include "templates/Lca.h"

vector<int> adj[100009];
int order[100009];
int weight[100009];
int parent[100009];
int map[100009];
int total_so_far = 0;

class Custom_SegmentTree: public PersistentTree<int> {
	public:

	int combine(int x,int y)
	{
		return x+y;
	}

	int update_combine(int x,int y)
	{
		return x+y;
	}

	int identity_element()
	{
		return 0;
	}

	int query_special(int u,int v,int lcaV,int parentLca,int k)
	{
		node *uRoot = tree.at(u);
		node *vRoot = tree.at(v);
		node *lcaRoot = tree.at(lcaV);
		node *parentRoot = NULL;
		if(parentLca!=-1) {
			parentRoot = tree.at(parentLca);
		}
		int lo=0,hi=size-1;
		while(lo!=hi)
		{
			int mid = lo + (hi-lo)/2;
			int num = uRoot->left->info + vRoot->left->info - lcaRoot->left->info - ((parentLca!=-1)?parentRoot->left->info:0);
			if(num<k)
			{
				uRoot = uRoot->right;
				vRoot = vRoot->right;
				lcaRoot = lcaRoot->right;
				if(parentLca!=-1)
					parentRoot = parentRoot->right;
				lo = mid+1;
				k = k-num;
			}
			else
			{
				uRoot = uRoot->left;
				vRoot = vRoot->left;
				lcaRoot = lcaRoot->left;
				if(parentLca!=-1)
					parentRoot = parentRoot->left;
				hi = mid;
			}
		}
		return lo;
	}

} tree;

void dfs(int v, int prev,int sequence)
{
	total_so_far++;
	order[v] = total_so_far;
	parent[v] = prev;
	tree.update(weight[v],weight[v],1,sequence);
	int size = adj[v].size();
	for(int i=0;i<size;i++)
	{
		int newV = adj[v][i];
		if(prev!=newV)
		{
			dfs(newV,v,order[v]);
		}
	}
}

void solve_input()
{
	pair<int,int> f[100009];
	int arr[100009]={0};
	int n,m;
	scanf("%d%d",&n,&m);
	Lca lcaTree(n);
	for(int i=0;i<n;i++)
	{
		int w;
		scanf("%d", &w);
		f[i] = make_pair(w,i);
	}
	sort(f,f+n);
	weight[f[0].second+1]=0;
	map[weight[f[0].second+1]]=f[0].first;
	for(int i=1;i<n;i++)
	{	
		if(f[i].first!=f[i-1].first)
		{	
			weight[f[i].second+1] = weight[f[i-1].second+1]+1;
			map[weight[f[i].second+1]] = f[i].first;
		}
		else
			weight[f[i].second+1] = weight[f[i-1].second+1];
	}
	tree.construct_tree(arr,n);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		lcaTree.addEdge(u,v);
	}
	lcaTree.initialize();
	dfs(1,0,0);
	order[0]=-1;
	while(m--)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		int lcaV = lcaTree.lca(u,v);
		int parentLca = parent[lcaV];
		int res = tree.query_special(order[u],order[v],order[lcaV],order[parentLca],k);
		printf("%d\n",map[res]);
	}
}

int main()
{
	solve_input();
	return 0;
}