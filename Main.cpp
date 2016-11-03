#include <cstdio>
#include <vector>
#include <algorithm>
#define pii pair<long long,long long>
#define mk_pii make_pair
using namespace std;
#include "templates/PersistentTree.h"
#include "templates/Lca.h"
#include "templates/HeavyLight.h"

class Custom_SegmentTree: public PersistentTree<pii> 
{
	public:

	pii combine(pii x,pii y)
	{
		return mk_pii(x.first+y.first,x.second+y.second);
	}

	pii lazy_combine(pii x,pii y)
	{
		return mk_pii(x.first+y.first,x.second+y.second);
	}

	pii identity_element()
	{
		return mk_pii(0,0);
	}

	pii apply_update(pii x,pii y,int n)
	{
		return mk_pii(x.first + (long long)n*y.first+((long long)n*(n-1)/2)*y.second,0);
	}

} *tree;

void solve_input()
{
	pii arr[100009];
	int n,m;
	scanf("%d%d",&n,&m);
	Lca lcaTree(n);
	HeavyLight hldTree(n);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d%d", &u, &v);
		lcaTree.addEdge(u,v);
		hldTree.addEdge(u,v);
	}
	lca.initialize();
	hld.initialize();
	int totalChains = hld.total_chains();
	tree = new Custom_SegmentTree[totalChains];
	for(int i=0;i<totalChains;i++)
	{
		int u = hld.first_vertex(i);
		int size=0;
		while(u!=-1)
		{
			arr[size]= mk_pii(0,0);
			size++;
			u = hld.next(u);
		}
		tree[i].construct_tree(arr,size);
	}
	int lastans=0,update_queries=0;
	while(m--)
	{
		char type;
		scanf("%c",&type);
		if(type=='l')
		{
			int x1;
			scanf("%d",&x1);
			int x = (x1+lastans)%(update_queries+1);
		}
		else if(type=='c')
		{
			int x1,y1,A,B;
			scanf("%d%d%d%d",&x1,&y1,&A,&B);
			int x = (x1+lastans)%n+1, y = (y1+lastans)%n+1;
			update_queries++;
		}
		else
		{
			int x1,y1;
			scanf("%d%d",&x1,&y1);
			int x = (x1+lastans)%n+1, y = (y1+lastans)%n+1;
		}
	}
}

int main()
{
	solve_input();
	return 0;
}