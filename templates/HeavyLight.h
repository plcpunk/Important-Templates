#include <vector>

class HeavyLight {

    std::vector<int> *adj;
    std::pair<int,int> *vertexToChainMap;
    int *firstChainVertex;
    int *specialChild;
    int *parent;
    int size;
    int totalChains;

    int subTreeHelper(int v,bool *vis)
    {
        vis[v] = true;
        int res = 1;
        int maxSize = 0;
        int special = -1;
        for(int i=0;i<adj[v].size();i++)
        {
            int newV = adj[v][i];
            if(!vis[newV])
            {
                parent[newV] = v;
                int val = subTreeHelper(newV,vis);
                if(val>maxSize)
                {
                    special = newV;
                    maxSize = val;
                }
                res+=val;
            }
        }
        specialChild[v]=special;
        return res;
    }

    void decompositionHelper(int v, int index)
    {
        vertexToChainMap[v] = std::make_pair(totalChains,index);
        if(index==0)
            firstChainVertex[totalChains] = v;
        if(specialChild[v]!=-1)
            decompositionHelper(specialChild[v],index+1);
        for(int i=0;i<adj[v].size();i++)
        {
            int newV = adj[v][i];
            if(newV!=parent[v] && specialChild[v] != newV)
            {
                totalChains++;
                decompositionHelper(newV,0);
            }
        }
    }

    public:

    HeavyLight(int n)
    {
        size = n;
        totalChains = 0;
        adj = new std::vector<int>[size+9];
        vertexToChainMap = new std::pair<int,int>[size+9];
        firstChainVertex = new int[size+9];
        specialChild = new int[size+9];
        parent = new int[size+9];
    }

    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void initialize()
    {
        bool *vis = new bool[size+9]();
        parent[1] = -1;
        subTreeHelper(1,vis);
        decompositionHelper(1,0);
        totalChains++;
    }

    int next(int v)
    {
        return specialChild[v];
    }

    int prev(int v)
    {
        return parent[v];
    }

    int index(int v)
    {
        return vertexToChainMap[v].second;
    }

    int chain_number(int v)
    {
        return vertexToChainMap[v].first;
    }

    int first_vertex(int chain)
    {
        return firstChainVertex[chain];
    }

    int total_chains()
    {
        return totalChains;
    }
};