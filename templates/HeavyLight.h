#include <vector>

class HeavyLight {

    std::vector<int> *adj;
    std::pair<int,int> *vertexToChainMap;
    int *firstChainVertex;
    int *specialChild;
    int *parent;
    int size;

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

    int decompositionHelper(int v,int chain,int firstVertex, int index)
    {
        vertexToChainMap[v] = std::make_pair(chain,index);
        firstChainVertex[chain] = firstVertex;
        for(int i=0;i<adj[v].size();i++)
        {
            int newV = adj[v][i];
            if(newV!=parent[v])
            {
                if(specialChild[v] == newV)
                    decompositionHelper(newV,chain,firstVertex,index+1);
                else
                    decompositionHelper(newV,chain+1,newV,0);
            }
        }
    }

    public:

    HeavyLight(int n)
    {
        size = n;
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
        bool *vis = new bool[size+9];
        parent[1] = -1;
        subTreeHelper(1,vis);
        decompositionHelper(1,0,1,0);
    }
};