
class DSU 
{
    int *parent;
    int *rank;
    int *size;

    public:

    DSU(int n) 
    {
        parent = new int[n+9];
        rank = new int[n+9];
        size = new int[n+9];
        for(int i=1;i<=n;i++)
        {
            parent[i]=i;
            rank[i]=0;
            size[i]=1;
        }
    }

    int find(int x)
    {
        if(parent[x]!=x)
            parent[x]=find(parent[x]);
         return parent[x];   
    }

    bool Union(int x,int y)
    {
        int u = find(x);
        int v = find(y);
        if(u==v)
            return false;
        if(rank[u]<rank[v])
        {
            parent[u] = v;
            size[v]+=size[u];
        }
        else if(rank[u]>rank[v])
        {
            parent[v] = u;
            size[u]+=size[v];
        }
        else
        {
            parent[v] = u;
            size[u]+=size[v];
            rank[u]++;
        }
        return true;
    }
};