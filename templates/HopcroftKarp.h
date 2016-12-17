#include <vector>
#include <queue>

class HopcroftKarp
{
	vector<int> *adj;
	int *match;
	vector<int> left;
	vector<int> right;
	int *d;
	int NIL;
	int inf;
 
    public:
 
    HopcroftKarp(vector<int> left_list,vector<int> right_list)
    {
    	left=left_list;
    	right=right_list;
    	NIL=left.size()+right.size();
	    adj = new vector<int>[NIL+9];
	    match = new int[NIL+9];
	    d = new int[NIL+9];
	    inf=NIL+3;
    }

    void addEdge(int u,int v)
    {
	    adj[u].push_back(v);
	    adj[v].push_back(u);
    }

    bool bfs()
    {
	    queue<int> q;
	    for(int i=0;i<left.size();i++)
	    {
		    if(match[left[i]]==NIL)
		    {
			    d[left[i]]=0;
			    q.push(left[i]);
		    }
		    else
			    d[left[i]]=inf;
	    }
	    d[NIL]=inf;
	    while(!q.empty())
	    {
		    int u=q.front();q.pop();
		    if(d[u]<d[NIL])
		    {
			    for(int i=0;i<adj[u].size();i++)
			    {
				    if(d[match[adj[u][i]]]==inf)
				    {
					    d[match[adj[u][i]]]=d[u]+1;
					    q.push(match[adj[u][i]]);
				    }
			    }
		    }
	    }
	    return d[NIL]!=inf;
    }
 
    bool dfs(int u)
    {
	    if(u==NIL)
		    return true;
	    for(int i=0;i<adj[u].size();i++)
	    {
		    if(d[match[adj[u][i]]]==d[u]+1 && dfs(match[adj[u][i]]))
		    {
			    match[u]=adj[u][i];
			    match[adj[u][i]]=u;
			    return true;
		    }
	    }
	    d[u]=inf;
	    return false;
    }
 
    int getMaxMatching()
    {
	    for(int i=0;i<left.size();i++)
		    match[left[i]]=NIL;
	    for(int i=0;i<right.size();i++)
		    match[right[i]]=NIL;
	    int matching=0;
	    while(bfs())
		    for(int i=0;i<left.size();i++)
			    if(match[left[i]]==NIL && dfs(left[i]))
				    matching++;
	    return matching;
    }
 
    int getMatchVertex(int v)
    {
	    return match[v];
    }
};