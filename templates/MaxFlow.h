#include <queue>
#include <vector>

class MaxFlow
{
    int size;
    vector<int> *adj;
    int **cap;
    int *height;
    int *excess;
    int **flow;

    public:
    
    MaxFlow(int n)
    {
        size = n;
        adj = new vector<int>[n+9];
        height = new int[n+9];
        excess = new int[n+9];
        cap = new int*[n+9];
        flow = new int*[n+9];
      	for(int i=0;i<n;i++)
      	{
            cap[i] = new int[n+9];
            flow[i] = new int[n+9];
            height[i] = 0;
            excess[i] = 0;
            for(int j=0;j<n;j++)
            {    
                cap[i][j]=0;
                flow[i][j]=0;
            }
        }
    }

    void addEdge(int u,int v,int c)
    {
        if(cap[u][v]==0 && cap[v][u]==0)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cap[u][v] = c;
    }

    void initializePreflow(int s)
    {
        for(int i=0;i<adj[s].size();i++)
        {
            int v = adj[s][i];
            flow[s][v] = cap[s][v];
            flow[v][s] = -flow[s][v];
            excess[v] = flow[s][v];
            excess[s] = -flow[s][v];
        }
    }

    void push(int u,int v)
    {
        int flowAmt = min(excess[u],cap[u][v]-flow[u][v]);
        flow[u][v] += flowAmt;
        flow[v][u] = -flow[u][v];
        excess[v] += flowAmt;
        excess[u] -= flowAmt;
    }

    void maxFlow(int s,int t)
    {
        initializePreflow(s);
        height[s] = size;
        queue<int> q;
        bool *mark = new bool[size+9];
        for(int i=0;i<size;i++)
            mark[i] = false;
        for(int i=0;i<adj[s].size();i++)
        {
            int v = adj[s][i];
            if(v!=t)
            {
                q.push(v);
                mark[v] = true;
            }
        }
        while(!q.empty())
        {
            int u = q.front();
            int m = -1;
            for(int i=0;i<adj[u].size() && excess[u]>0;i++)
            {
                int v = adj[u][i];
                if(cap[u][v] - flow[u][v] > 0)
                {
                    if(height[u] > height[v])
                    {
                        push(u,v);
                        if(!mark[v] && v!=t && v!=s)
                        {
                            q.push(v);
                            mark[v] = true;
                        }
                    }
                    else if(m==-1)
                        m = height[v];
                    else
                        m = min(m,height[v]);
                }
            }
            if(excess[u]!=0)
                height[u] = m+1;
            else
            {
                mark[u] =false;
                q.pop();
            }
        }
    }

    int getExcess(int v)
    {
        return excess[v];
    }

    int getFlow(int u,int v)
    {
        return flow[u][v];
    }
};