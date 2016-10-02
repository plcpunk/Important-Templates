#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "templates/SegmentTree.h"
#include "templates/HeavyLight.h"
#include "templates/Lca.h"

class Custom_SegmentTree: public SegmentTree<int> {
	public:

	int combine(int x,int y)
	{
		return max(x,y);
	}

	int update_combine(int x,int y)
	{
		if(y==-1)
			return x;
		return y;
	}

	int identity_element()
	{
		return -1;
	}

};

void solve_input()
{
	Custom_SegmentTree *tree;
	pair<int,int> edge[10009];
	int tmp[10009];
	int weight[10009];
	int n;
	scanf("%d",&n);
	Lca lca(n);
	HeavyLight hld(n);
	for(int i=0;i<n-1;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		lca.addEdge(u,v);
		hld.addEdge(u,v);
		edge[i] = make_pair(u,v);
		tmp[i] = w;
	}
	lca.initialize();
	hld.initialize();
	for(int i=0;i<n-1;i++)
	{
		int u = edge[i].first;
		int v = edge[i].second;
		if(hld.prev(u)==v)
		{
			weight[u]=tmp[i];
		}
		else
		{
			weight[v]=tmp[i];
		}
	}
	int totalChains = hld.total_chains();
	tree = new Custom_SegmentTree[totalChains];
	for(int i=0;i<totalChains;i++)
	{
		int size=0;
		int v = hld.first_vertex(i);
		while(1)
		{
			int next = hld.next(v);
			if(next==-1)
				break;
			tmp[size]=weight[next];
			v = next;
			size++;
		}
		tree[i].construct_tree(tmp,size);
	}
	while(1)
	{
		char str[10];
		char change[10]="CHANGE";
		char query[10]="QUERY";
		scanf("%s",&str);
		if(strcmp(str,change)==0)
		{
			int index,t,vertex;
			scanf("%d%d",&index,&t);
			int u = edge[index-1].first;
			int v = edge[index-1].second;
			if(hld.prev(u)==v)
				vertex = u;
			else
				vertex = v;
			int i = hld.index(vertex);
			int chainNumber = hld.chain_number(vertex);
			weight[vertex] = t;
			tree[chainNumber].update(i-1,i-1,t);
		}
		else if(strcmp(str,query)==0)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			int lcaV = lca.lca(u,v);
			int res = -1;
			if(u!=lcaV)
			{
				int ch = hld.chain_number(lcaV);
				int vertex = hld.next(lcaV);
				while(ch!=hld.chain_number(u))
				{
					int num = hld.chain_number(u);
					res = max(res,tree[num].query(0,hld.index(u)-1));
					res = max(res,weight[hld.first_vertex(num)]);
					u = hld.prev(hld.first_vertex(num));
				}
				res = max(res,tree[ch].query(hld.index(vertex)-1,hld.index(u)-1));
			}
			if(v!=lcaV)
			{
				int ch = hld.chain_number(lcaV);
				int vertex = hld.next(lcaV);
				while(ch!=hld.chain_number(v))
				{
					int num = hld.chain_number(v);
					res = max(res,tree[num].query(0,hld.index(v)-1));
					res = max(res,weight[hld.first_vertex(num)]);
					v = hld.prev(hld.first_vertex(num));
				}
				res = max(res,tree[ch].query(hld.index(vertex)-1,hld.index(v)-1));
			}
			printf("%d\n",res);
		}
		else
		{
			break;
		}
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve_input();
	return 0;
}